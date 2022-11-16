/*==========================================================*
 *
 * @author Gustaf Franzén :: https://github.com/BjorneEk;
 *
 * Util-Library function type definitions
 *
 *==========================================================*/

#ifndef _UL_FUNCTION_H_
#define _UL_FUNCTION_H_

#include "types.h"

typedef i32_t (*compare_f)(const void *a, const void *b);
typedef bool  (*predicate_f)(const void *arg);
typedef void  (*action_f)(const void *arg);
typedef void  (*noreturn_f)(void *arg);
typedef void  *(*returning_f)(const void *arg);
#endif /* _UL_FUNCTION_H_ */
