/*==========================================================*
 *
 * @author Gustaf Franzén :: https://github.com/BjorneEk;
 *
 * Util-Library IO res
 *
 *==========================================================*/
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "IO.h"
#include "assert.h"
#include "general.h"
#include <errno.h>

i32_t read_file(const char * filename, char * res)
{
  size_t new_len;
  long buffer_size;
  FILE * fp;

  fp = fopen(filename, "r");
  assert(fp != NULL, "could not read from file");
  /* Go to the end of the file. */
  if (fseek(fp, 0L, SEEK_END) == 0) {
    /* Get the size of the file. */
    buffer_size = ftell(fp);
    assert(buffer_size != -1, "Error reading file");
    /* Allocate our buffer to that size. */
    res = malloc(sizeof(char) * (buffer_size + 1));
    assert(res != NULL, "Out of memory");

    /* Go back to the start of the file. */
    assert(fseek(fp, 0L, SEEK_SET) == 0, "Error reading file");

    /* Read the entire file into memory. */
    new_len = fread(res, sizeof(char), buffer_size, fp);

    assert(ferror( fp ) == 0, "Error reading file");
    res[new_len++] = '\0'; /* Just to be safe. */
  }
  fclose(fp);
  return new_len;
}

bool is_repetition(const u8_t * data, i32_t i)
{
  return memcmp(&data[i], &data[i - 0x10], 0x10);
}

void hexdump(const u8_t * data, u64_t len)
{
  u32_t i, j, k, cnt;
  u8_t r;

  printf("┌─────────┬─────────────────────────┬─────────────────────────┬────────┬────────┐\n");

  for (i = r = cnt = 0; i < len; i += 0x10) {
    if(i != 0 && !is_repetition(data, i)){
      r = 1; cnt++; continue;
    }

    if (r) {
      printf("│*%7i │                         │                         │        │        │\n",cnt);
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
        if(is_ascii(data[i+k+(j*0x8)])) {
          printf("%c", (char)data[i+k+(j*0x8)]);
        } else if(data[i+k+(j*0x8)] == 0) {
          printf("0");
        } else {
          printf("×");
        }
      }
      j++;
    }
    printf("│");
    printf("\n");
  }
  printf("└─────────┴─────────────────────────┴─────────────────────────┴────────┴────────┘\n");
}
