/*==========================================================*
 *
 * @author Gustaf Franzén :: https://github.com/BjorneEk;
 *
 * Util-Library Math utils
 *
 *==========================================================*/

#ifndef _MATH_H_
#define _MATH_H_

#include "types.h"

#define RAND_MAX 0x7fffffff

/**
 * the lowest 16 bits in a 32 bit integer
 **/
#define LOW_16(address)  ((u16_t)((address) & 0xFFFF))
/**
 * the highest 16 bits in a 32 bit integer
 **/
#define HIGH_16(address) ((u16_t)(((address) >> 16) & 0xFFFF))

/**
 * the lowest 8 bits in a 16 bit integer
 **/
#define LOW_8(word)  ((u8_t)((word) & 0xFF))
/**
 * the highest 8 bits in a 16 bit integer
 **/
#define HIGH_8(word) ((u8_t)(((word) >> 8) & 0xFF))


#define COSF(_x) ((f32_t)cos(_x))
#define SINF(_x) ((f32_t)sin(_x))

#define MAX(a, b) ({\
  __typeof__ (a) _a = (a); \
  __typeof__ (b) _b = (b); \
   _a > _b ? _a : _b; })

#define MIN(a, b) ({\
  __typeof__ (a) _a = (a); \
  __typeof__ (b) _b = (b); \
  _a < _b ? _a : _b; })

/**
 * returns a random f64_t within the specified range [min, max)
 **/
#define randf(min, max) ((min) + ((f64_t) rand() / ((f64_t) RAND_MAX + 1)) * ((max) - (min)))
/**
 * returns a random int within the specified range [min, max] using the randf function
 **/
#define randi(min, max) ((i32_t)(randf((min), ((max)+1))))

/**
 * remaps a value v from a range a1 -> a2 to a range b1 -> b2,
 * for example 2 in the range (0 -> 10) mapped to the rnage (0 -> 100) is 20
 **/
#define remap(v,a1,a2,b1,b2) ((b1) + ((v) - (a1)) * ((b2) - (b1)) / ((a2) - (a1)))

#endif /* _MATH_H_ */
