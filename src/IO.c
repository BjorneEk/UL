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
#include <sys/stat.h>
#include <unistd.h>
#include <string.h>

i64_t get_filesize(const char *fname)
{
        struct stat sb;
        stat(fname, &sb);
        return sb.st_size;
}

BOOL remove_file(const char *fname)
{
        i32_t res;
        res = remove(fname);
        return  !!res;
}

void create_file(const char *fname)
{
        FILE *fp;
        fp = fopen(fname, "a");
        assertf(fp != NULL, "could not create file: %s", fname);
        fclose(fp);
}

BOOL rename_file(const char *src, const char *fname)
{
        i32_t res;
        res = rename(src, fname);
        return  !!res;
}

BOOL file_exists(const char *fname)
{
        return !access(fname, F_OK);
}

BOOL file_can_read(const char *fname)
{
        return !access(fname, R_OK);
}

BOOL file_can_write(const char *fname)
{
        return !access(fname, W_OK);
}

BOOL file_can_exec(const char *fname)
{
        return !access(fname, X_OK);
}



u8_t * WUNUSED read_file(const char *fname, i64_t *len)
{
        i64_t flen;
        FILE *fp;
        u8_t *res;
        i32_t er;
        fp = fopen(fname, "r");
        assertf(fp != NULL, "could not open file: '%s' for reading", fname);

        flen = get_filesize(fname);

        assertf_to(flen > 0, exit,
                "reading file: %s, filesize: %li", fname, flen);

        res = malloc(sizeof(char) * (flen + 1));
        assertf_to(res != NULL, exit, "Out of memory (read_file): %s", fname);

        fread(res, sizeof(char), flen, fp);

        er = ferror(fp);
        assertf_to(er == 0, exit_free_res, "reading file: %s", fname);

        fclose(fp);
        if (len != NULL) *len = flen;
        return res;

exit_free_res:
        free(res);
exit:
        fclose(fp);
        exit(-1);
}

char * WUNUSED read_sfile(const char *fname, i64_t *len)
{
        char * res;
        i64_t flen;
        res = (char*)read_file(fname, &flen);
        res[flen]  = '\0';
        if (len != NULL) *len = flen;
        return res;
}
static void nwrite_file_mode(const char *fname, const char *str, u64_t n, const char *mode)
{
        FILE *fp;
        u64_t wbytes;
        fp = fopen(fname, mode);
        assertf(fp != NULL, "could not open file: '%s' for writing", fname);

        wbytes = fwrite(str, sizeof(char), n, fp);
        assertf_to(wbytes == n,
                exit, "writing to '%s', wrote %llu bytes instead of expected %llu bytes",
                fname, wbytes, n);
        fclose(fp);
        return;
exit:
        fclose(fp);
        exit(-1);
}

void nwrite_file(const char *fname, const char *str, u64_t n)
{
        nwrite_file_mode(fname, str, n, "w");
}

void write_file(const char *fname, const char *str)
{
        nwrite_file(fname, str, strlen(str));
}

void nappend_file(const char *fname, const char *str, u64_t n)
{
        nwrite_file_mode(fname, str, n, "a");
}

void append_file(const char *fname, const char *str)
{
        nwrite_file_mode(fname, str, strlen(str), "a");
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
