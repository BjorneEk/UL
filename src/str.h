
/*==========================================================*
 *
 * @author Gustaf Franzén :: https://github.com/BjorneEk;
 *
 * Util-Library string functions
 *
 *==========================================================*/

#ifndef _UL_UTIL_H_
#define _UL_UTIL_H_

#include "types.h"
#include "macro.h"
/**
 * returns true if i is a ascii character
 **/
bool is_ascii(i32_t i);

/**
 * retuns the index of ch in str
 **/
i64_t indexof(const char * str, char ch);

/**
 * places *c at the index of ch in *c or at the end if no instance exists
 **/
void moveto(char ** c, char ch);

/**
 * returns the number of digits in a int
 **/
u32_t nbr_of_digits(u64_t n, u32_t base);

/**
 * converts a int array to a string, (allocates the string)
 **/
char * WUNUSED iarrtos(i32_t * data, i64_t length);

/**
 * converts a double array to a string, (allocates the string)
 **/
char * WUNUSED farrtos(f64_t * data, i64_t length);


/**
 * returns the number of words in a string where words are separated by delim
 **/
u64_t strcnt(const char * buff, char delim);



/**
 * converts a CSV string array to a int array, returns the length
 *
 * @param res: the result
 * @param data: the input string
 * @param del: the delimitor used to separate the data in the string
 **/
i64_t CSV_iarr(i32_t ** res, char * data, char del);

/**
 * converts a string array to a double array, returns the length
 *
 * @param res: the result
 * @param data: the input string
 * @param del: the delimitor used to separate the data in the string
 **/
i64_t CSV_farr(f64_t ** res, char * data, char del);

#endif /* _UL_UTIL_H_ */
