/*==========================================================*
 *
 * @author Gustaf Franzén :: https://github.com/BjorneEk;
 *
 * Util-Library IO header
 *
 *==========================================================*/

#ifndef _IO_H_
#define _IO_H_

#include "types.h"


/**
 *  allocates space and reads the file contents from the file into the
 *  res string, returns the length of the string
 **/
i64_t read_file(const char * filename, char * res);

/**
 *  prints (len) bytes of data in hexdump format
 **/
void hexdump(const u8_t * data, u64_t len);

#endif /* _IO_H_ */
