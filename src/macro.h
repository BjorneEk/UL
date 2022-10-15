/*==========================================================*
 *
 * @author Gustaf Franzén :: https://github.com/BjorneEk;
 *
 * general macros
 *
 *==========================================================*/

#ifndef _UL_MACRO_H_
#define _UL_MACRO_H_

#define PACKED        __attribute__((__packed__))
#define WUNUSED       __attribute__((warn_unused_result))
#define ALWAYS_INLINE __attribute__((always_inline))
#define COLD          __attribute__((cold))
#define CONST         __attribute__ ((const))
#define DEPRICIATED   __attribute__ ((deprecated)) // can take a string argument
#define PURE          __attribute__ ((pure))
#define CAT(a, ...) PRIMITIVE_CAT(a, __VA_ARGS__)
#define PRIMITIVE_CAT(a, ...) a ## __VA_ARGS__


#endif /* _UL_MACRO_H_ */
