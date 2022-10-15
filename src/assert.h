/*==========================================================*
 *
 * @author Gustaf Franzén :: https://github.com/BjorneEk;
 *
 * Util-Library assert and warning functions
 *
 *==========================================================*/

#ifndef _UL_ASSERT_H_
#define _UL_ASSERT_H_

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include "types.h"
#include "macro.h"

extern char *strerror(int errnum);
extern int memcmp(const void *a, const void *b, unsigned long l);

#define ERR_LBL  "[\033[31;1;4mError\033[0m]"
#define WARN_LBL "[\033[33;1;4mWarning\033[0m]"


#define log_err(_fmt, ...) do {                                                 \
        fprintf(stderr, ERR_LBL ": " _fmt, __VA_ARGS__);                        \
        } while(0)

#define log_warn(_fmt, ...) do {                                                \
        fprintf(stderr, WARN_LBL ": " _fmt, __VA_ARGS__);                       \
        } while(0)

/*
 *  if as_ is false log the formated error and exit
 */
#define assertf(as_, format, ...) do{                                           \
        if(!(as_)) {                                                            \
                log_err(format, __VA_ARGS__);                                   \
                exit(1);                                                        \
        }                                                                       \
        }while(0)
/*
 *  if as_ is false log the formated error goto exit label
 */
#define assertf_to(as_, exit, format, ...) do{                                  \
        if(!(as_)) {                                                            \
                log_err(format, __VA_ARGS__);                                   \
                goto exit;                                                      \
        }                                                                       \
        }while(0)

/*
 *  if as_ is false log a error and exit whith status 1
 */
#define assert(c_) assertf(c_, "assertion error")
/*
 *  if as_ is false log a error and goto lbl
 */
#define assert_to(c_, lbl) assertf_to(c_, lbl, "assertion error")

#endif /* _UL_ASSERT_H_ */
