/*==========================================================*
 *
 * @author Gustaf Franzén :: https://github.com/BjorneEk;
 *
 * Util-Library hash functions header
 *
 *==========================================================*/
#ifndef _UL_HASH_H_
#define _UL_HASH_H_

#include <UL/types.h>

typedef u64_t (*hash_f)(const void *a, u64_t size);


/**
 * a fnv-1a hash algorithm.
 * https://en.wikipedia.org/wiki/Fowler–Noll–Vo_hash_function
 *
 * @param a   : the data to generate hash from,
 * @param size: the length in bytes of @a
 **/
u64_t HASH_fnv_1a(const void* a, u64_t size);


#endif /* _UL_HASH_H_ */
