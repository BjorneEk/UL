/*==========================================================*
 *
 * @author Gustaf Franzén :: https://github.com/BjorneEk;
 *
 * Util-Library type definitions
 *
 *==========================================================*/

#ifndef _UL_TYPES_H_
#define _UL_TYPES_H_

#include <stdbool.h>



typedef unsigned char      u8_t;
typedef unsigned short     u16_t;
typedef unsigned int       u32_t;
typedef unsigned long long u64_t;

typedef signed char        i8_t;
typedef signed short       i16_t;
typedef signed int         i32_t;
typedef signed long        i64_t;

typedef u8_t BOOL;

typedef float              f32_t;
typedef double             f64_t;


typedef i32_t (*compare_f)(const void *a, const void *b);

#endif /* _TYPES_H_ */
