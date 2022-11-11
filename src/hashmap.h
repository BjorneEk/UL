/*==========================================================*
 *
 * @author Gustaf Franzén :: https://github.com/BjorneEk;
 *
 * Util-Library generic hashmap
 *
 *==========================================================*/

#ifndef _UL_HASHMAP_H_
#define _UL_HASHMAP_H_

#include "hash.h"
#include <UL/types.h>


struct kvpair
{
        void *key;
        u64_t kwidth;

        void *value;
};

struct bucket
{
        u64_t hash;

        struct kvpair kvp;

        struct bucket *next;
};

typedef struct
{
        struct bucket *buckets;

        u64_t vwidth;

        u64_t len;
        u64_t allocated;

        hash_f hashf;
} hashmap_t;



/**
 * allocates and returns a new hashmap with the given type,
 * length and hash functions
 *
 * @param vwidth: the size in bytes of the values to be stored in the hashmap
 * @param len   : the length of the hashmap
 * @param hashf : the hashfunction of the hashmap
 **/
hashmap_t *
      HMAP_new(u64_t vwidth, u64_t len, hash_f hashf);

/**
 * frees a hashmap and its contents fully, this includes freeing the
 * key and value pointers themselves
 *
 * @param m: the hashmap to be freed
 **/
void  HMAP_free(hashmap_t **m);

/**
 * frees a hashmap, this does not include freeing the
 * key and value pointers themselves
 *
 * @param m: the hashmap to be freed
 **/
void  HMAP_free_map(hashmap_t **m);

/**
 * returns true if the hashmap contains a entry with the given key
 *
 * @param m     : the hashmap
 * @param key   : the key to search for
 * @param kwidth: the width in bytes of the @key
 **/
bool  HMAP_contins_key(hashmap_t *m, const void *key, u64_t kwidth);

/**
 * if the hashmap contains the given key return the value, else return NULL
 *
 * @param m  : the hashmap
 * @param key: the key to search for
 * @param kwidth: the width in bytes of the @key
 **/
void *HMAP_get(hashmap_t *m, const void *key, u64_t kwidth);

/**
 * if the hashmap contains the given key return the corresponding bucket,
 * else return NULL
 *
 * @param m  : the hashmap
 * @param key: the key to search for
 * @param kwidth: the width in bytes of the @key
 **/
static struct bucket *
      HMAP_get_bucket(hashmap_t *m, const void *key, u64_t kwidth);

/**
 * adds the entry created by @key and @value to the hashmap
 *
 * @param m     : the hashmap
 * @param key   : the key to the entry
 * @param kwidth: the width in bytes of the @key
 * @param value : the value to be added
 **/
void  HMAP_add(hashmap_t *m, void *key, u64_t kwidth, void *value);

/**
 * returns a heap allocated array of all the kvpairs in the hashmap
 *
 * @param m: the hashmap
 **/
struct kvpair *
      HMAP_kvpairs(hashmap_t *m);

/**
 * changes the size of the hashmap, and its hash function and
 * appends all of its current entries to the resized
 * map using the new hash function
 *
 * @param m  : the hashmap
 * @param len: the new lenght of the hashmap
 * @param hashf: the new hash function.
 **/
void  HMAP_remake(hashmap_t *m, u64_t size, hash_f hashf);

/**
 * changes the hash function of the hashmap and rehashes all its values.
 *
 * @param m    : the hashmap
 * @param hashf: the new hash function.
 **/
void  HMAP_rehash(hashmap_t *m, hash_f hashf);

/**
 * changes the size of the hashmap and appends all of its current
 * entries to the resized map using the old hash function
 *
 * @param m  : the hashmap
 * @param len: the new lenght of the hashmap
 **/
void  HMAP_resize(hashmap_t *m, u64_t len);

#endif /* _UL_HASHMAP_H_ */
