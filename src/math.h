/*==========================================================*
 *
 * @author Gustaf Franzén :: https://github.com/BjorneEk;
 *
 * Util-Library Math utils
 *
 *==========================================================*/

#ifndef _UL_MATH_H_
#define _UL_MATH_H_

#include <math.h>
#include "types.h"

#define RAND_MAX 0x7fffffff


#define PI_HALF 1.57079632679489661923132169163975144
#define PI      3.14159265358979323846264338327950288
#define TWO_PI  6.28318530717958647692528676655900576

/**
 * RAD_IN_DEG = 180 / PI
 * DEG_IN_RAD = PI / 180
 **/
#define RAD_IN_DEG 57.295779513082320876798154814105170408
#define DEG_IN_RAD 0.017453292519943295769236907684886127

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

#define MAX(a, b) ({\
  __typeof__ (a) _a = (a); \
  __typeof__ (b) _b = (b); \
   _a > _b ? _a : _b; })

#define MIN(a, b) ({\
  __typeof__ (a) _a = (a); \
  __typeof__ (b) _b = (b); \
  _a < _b ? _a : _b; })

#define COSF(_x) ((f32_t)cos(_x))
#define SINF(_x) ((f32_t)sin(_x))
#define COS2F(_x) ((f32_t) (cos(_x) * cos(_x)) )
#define SIN2F(_x) ((f32_t) (sin(_x) * sin(_x)) )

#define deg_to_rad(_x) ((_x) * (__typeof__(_x)) (DEG_IN_RAD))
#define rad_to_deg(_x) ((_x) * (__typeof__(_x)) (RAD_IN_DEG))
#define sign(v) ((v > 0.0) - (v < 0.0))
#define clamp(v, min, max) (MIN(MAX((val), (min)), (max)))



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



#endif /* _UL_MATH_H_ */
