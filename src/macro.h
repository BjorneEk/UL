/*==========================================================*
 *
 * @author Gustaf Franzén :: https://github.com/BjorneEk;
 *
 * general macros
 *
 *==========================================================*/

#ifndef _UL_MACRO_H_
#define _UL_MACRO_H_

#define PACKED __attribute__((__packed__))

#define CAT(a, ...) PRIMITIVE_CAT(a, __VA_ARGS__)
#define PRIMITIVE_CAT(a, ...) a ## __VA_ARGS__

#endif /* _UL_MACRO_H_ */
