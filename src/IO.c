/*==========================================================*
 *
 * @author Gustaf Franzén :: https://github.com/BjorneEk;
 *
 * Util-Library IO res
 *
 *==========================================================*/

#include "IO.h"
#include "assert.h"
#include "str.h"


i64_t read_file_to(const char *fname, char **res)
{
        i64_t len;
        i64_t flen;
        FILE *fp;

        fp = fopen(fname, "r");
        assertf(fp != NULL, "could not read from file: %s", fname);

        if (fseek(fp, 0L, SEEK_END) == 0) {
                /* Get the size of the file. */
                flen = ftell(fp);
                assertf(flen != -1, "Error reading file: %s", fname);
                /* Allocate our buffer to that size. */
                *res = malloc(sizeof(char) * (flen + 1));
                assertf(*res != NULL, "Out of memory (read_file): %s", fname);

                /* Go back to the start of the file. */
                assertf(fseek(fp, 0L, SEEK_SET) == 0,"Error reading file: %s", fname);

                /* Read the entire file into memory. */
                len = fread(*res, sizeof(char), flen, fp);

                assertf(ferror( fp ) == 0, "Error reading file: %s", fname);
                *res[len] = '\0'; /* Just to be safe. */
        }
        return len;
}

char * WUNUSED read_file(const char *fname, i64_t *len)
{
        i64_t new_len;
        i64_t flen;
        FILE *fp;
        char * res;
        fp = fopen(fname, "r");
        assertf(fp != NULL, "could not read from file: %s", fname);

        if (fseek(fp, 0L, SEEK_END) == 0) {
                /* Get the size of the file. */
                flen = ftell(fp);
                assertf(flen != -1, "Error reading file: %s", fname);
                /* Allocate our buffer to that size. */
                res = malloc(sizeof(char) * (flen + 1));
                assertf(res != NULL, "Out of memory (read_file): %s", fname);

                /* Go back to the start of the file. */
                assertf(fseek(fp, 0L, SEEK_SET) == 0,"Error reading file: %s", fname);

                /* Read the entire file into memory. */
                new_len = fread(res, sizeof(char), flen, fp);

                assertf(ferror( fp ) == 0, "Error reading file: %s", fname);
                res[new_len] = '\0'; /* Just to be safe. */
        }
        if (len != NULL) *len = new_len;
        return res;
}

static inline BOOL is_repetition(const u8_t * data, i32_t i)
{
        return !!memcmp(&data[i], &data[i - 0x10], 0x10);
}

void hexdump(const u8_t * data, u64_t len)
{
        u32_t i, j, k, cnt;
        u8_t r;

        printf("┌─────────┬─────────────────────────┬───"
         "──────────────────────┬────────┬────────┐\n");

         for (i = r = cnt = 0; i < len; i += 0x10) {
                 if(i != 0 && !is_repetition(data, i))
                         r = 1; cnt++; continue;


                if (r) {
                        printf("│*%7i │                         │   "
                               "                      │        │        │\n",cnt);
                        r = cnt = 0;
                }

                printf("│%08x ", i);

                j = 0;
                while (j < 2) {
                        printf("│ ");
                        for(k = 0; k < 0x8; k++) printf("%02x ", data[i+k+(j*0x8)]);
                        j++;
                }

                j = 0;
                while (j < 2) {
                        printf("│");
                        for(k = 0; k < 0x8; k++) {
                                if(is_ascii(data[i+k+(j*0x8)]))
                                        printf("%c", (char)data[i+k+(j*0x8)]);
                                else if(data[i+k+(j*0x8)] == 0)
                                        printf("0");
                                else
                                        printf("×");
                        }
                        j++;
                }
                printf("│");
                printf("\n");
        }
        printf("└─────────┴─────────────────────────┴───"
               "──────────────────────┴────────┴────────┘\n");
}
