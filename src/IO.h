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
 * returns the size of the file in number of bytes
 **/
i64_t get_filesize(const char *fname);

/**
 *  allocates space and reads the file contents from
 *  the file as a \0 terminated char *, len is set to the length of the string
 **/
char * WUNUSED read_sfile(const char *fname, i64_t *len);

/**
 *  allocates space and reads the file contents from
 *  the file as a unsigned char *, len the bytes read
 **/
u8_t * WUNUSED read_file(const char *fname, i64_t *len);

/**
 * removed the file named @fname
 * @returns true if file was removed
 **/
BOOL remove_file(const char *fname);

/**
 * creates a file named @fname
 **/
void create_file(const char *fname);

/**
 * renames the file named @src to @fname
 * @returns true if successful
 **/
BOOL rename_file(const char *src, const char *fname);

/**
 * @returns true if there exists a file named @fname
 **/
BOOL file_exists(const char *fname);

/**
 * @returns true if program could read from @fname
 **/
BOOL file_can_read(const char *fname);

/**
 * @returns true if program could write to @fname
 **/
BOOL file_can_write(const char *fname);

/**
 * @returns true if program could execute @fname
 **/
BOOL file_can_exec(const char *fname);

/**
 * writes the contents of @str to a file named @fname,
 * if no such file exists, it creates it
 **/
void write_file(const char *fname, const char *str);

/**
 * writes the first @n bytes of @str to a file named @fname,
 * if no such file exists, it creates it
 **/
void nwrite_file(const char *fname, const char *str, u64_t n);

/**
 * appends the contents of @str to a file named @fname,
 * if no such file exists, it creates it
 **/
void append_file(const char *fname, const char *str);

/**
 * appends the first @n bytes of @str to a file named @fname,
 * if no such file exists, it creates it
 **/
void nappend_file(const char *fname, const char *str, u64_t n);


/**
 * copies the file named @src to @dst
 * @returns a IO_* result code
 **/
i32_t copy_file(const char *src, const char *dst);

/**
 *  prints (len) bytes of data in hexdump format
 **/
void hexdump(const u8_t *data, u64_t len);

#endif /* _UL_IO_H_ */
