/*==========================================================*
 *
 * @author Gustaf Franzén :: https://github.com/BjorneEk;
 *
 * Util-Library IO header
 *
 *==========================================================*/

#ifndef _UL_IO_H_
#define _UL_IO_H_

#include "types.h"
#include "macro.h"


/**
 *  allocates space and reads the file contents from the file into the
 *  res string, returns the length of the string
 **/
i64_t read_file_to(const char *fname, char **res);

/**
 *  allocates space and reads the file contents from
 *  the file as a char *, len is set to the length of the string
 **/
char * WUNUSED read_file(const char *fname, i64_t *len);

/**
 *  prints (len) bytes of data in hexdump format
 **/
void hexdump(const u8_t *data, u64_t len);

#endif /* _UL_IO_H_ */
