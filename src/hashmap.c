/*==========================================================*
 *
 * @author Gustaf Franzén :: https://github.com/BjorneEk;
 *
 * Util-Library hashmap functions
 *
 *==========================================================*/

#include "hashmap.h"
#include <assert.h>
#include <stdlib.h>
#include <string.h>

hashmap_t *
      HMAP_new(u64_t vwidth, u64_t len, hash_f hashf)
{
        hashmap_t *res;

        res             = malloc(sizeof (hashmap_t));
        res->buckets    = calloc(len, sizeof(struct bucket));
        res->vwidth     =     vwidth;
        res->allocated  =        len;
        res->hashf      =      hashf;
        res->len        =          0;
        return res;
}

static inline void
      free_bucket(struct bucket *b)
{
        free(b->kvp.key);
        free(b->kvp.value);
}

void  HMAP_free(hashmap_t **m)
{
        u64_t i;
        struct bucket *b, *tmp;

        for(i = 0; i < (*m)->allocated; i++){
                if ((*m)->buckets[i].kvp.value != NULL) {
                        free_bucket(&(*m)->buckets[i]);
                        b = (*m)->buckets[i].next;
                        while(b != NULL) {
                                tmp = b->next;
                                free_bucket(b);
                                free(b);
                                b = tmp;
                        }
                }
        }
        if((*m)->buckets != NULL)
                free((*m)->buckets);
        if(*m != NULL)
                free(*m);
}

void  HMAP_free_map(hashmap_t **m)
{
        u64_t i;
        struct bucket *b, *tmp;

        for(i = 0; i < (*m)->allocated; i++){
                if ((*m)->buckets[i].kvp.value != NULL) {
                        b = (*m)->buckets[i].next;
                        while(b != NULL) {
                                tmp = b->next;
                                free(b);
                                b = tmp;
                        }
                }
        }
        if((*m)->buckets != NULL)
                free((*m)->buckets);
        if(*m != NULL)
                free(*m);
}

u64_t HMAP_hash_idx(hashmap_t *m, const void *key, u64_t kwidth)
{
        return m->hashf(key, kwidth) % m->allocated;
}

i64_t HMAP_index_of_hash(hashmap_t *m, u64_t hash)
{
        struct bucket *entry;
        u64_t i;

        i = hash % m->allocated;
        entry = &m->buckets[i];

        if (entry != NULL && entry->hash == hash)
                return i;

        for(i = 0; i < m->allocated; i++)
                if(m->buckets[i].hash == hash)
                        return i;

        return -1;
}



static struct bucket *
      HMAP_get_bucket(hashmap_t *m, const void *key, u64_t kwidth)
{
        struct bucket *e;
        u64_t i, hash;

        hash = m->hashf(key,kwidth);
        i = hash % m->allocated;
        e = &m->buckets[i];

        do {
                if (e->hash == hash &&
                    e->kvp.kwidth == kwidth &&
                    memcmp(e->kvp.key, key, kwidth) == 0) {
                        return e;
                }
                e = e->next;
        } while(e != NULL);
        return NULL;
}

bool  HMAP_contins_key(hashmap_t *m, const void *key, u64_t kwidth)
{
        return HMAP_get_bucket(m, key, kwidth) != NULL;
}

void *HMAP_get(hashmap_t *m, const void *key, u64_t kwidth)
{
        struct bucket *entry;

        entry = HMAP_get_bucket(m, key, kwidth);

        if(entry == NULL)
                return NULL;
        do{
                if(entry->kvp.kwidth == kwidth &&
                   memcmp(entry->kvp.key, key, kwidth) == 0)
                         return entry->kvp.value;

                entry = entry->next;

        }while(entry->next != NULL);

        return NULL;
}

struct bucket
      new_bucket(hashmap_t *m, void *key, u64_t kwidth, void *value)
{
        struct bucket res;

        res.kvp.value = value;
        res.kvp.key   =   key;

        res.hash       = m->hashf(key, kwidth);
        res.next       =                  NULL;
        res.kvp.kwidth =                kwidth;
        return res;
}
struct bucket *
   new_bucketptr(hashmap_t *m, void *key, u64_t kwidth, void *value)
{
        struct bucket *res;

        res            = malloc(sizeof(struct bucket));

        *res = new_bucket(m, key, kwidth, value);
        return res;
}



void  HMAP_add(hashmap_t *m, void *key, u64_t kwidth, void *value)
{
        u64_t i;
        struct bucket *b;

        m->len++;
        i = HMAP_hash_idx(m, key, kwidth);

        if(m->buckets[i].kvp.key == NULL) {
                m->buckets[i] = new_bucket(m, key, kwidth, value);
        } else {
                for(b = &m->buckets[i]; b->next != NULL; b = b->next)
                        ;
                b->next = new_bucketptr(m, key, kwidth, value);
        }
}

void  HMAP_addcpy(hashmap_t *m, void *key, u64_t kwidth, void *value)
{
        void *kcpy;
        void *vcpy;

        kcpy = malloc(kwidth);
        vcpy = malloc(m->vwidth);
        memcpy(kcpy, key, kwidth);
        memcpy(vcpy, value, m->vwidth);
        HMAP_add(m, kcpy, kwidth, vcpy);
}
void  HMAP_add_kvpair(hashmap_t *m, struct kvpair kvp)
{
        u64_t i;
        struct bucket *b;

        m->len++;
        i = HMAP_hash_idx(m, kvp.key, kvp.kwidth);

        if(m->buckets[i].kvp.key == NULL) {
                m->buckets[i] = new_bucket(m, kvp.key, kvp.kwidth, kvp.value);
        } else {
                for(b = &m->buckets[i]; b->next != NULL; b = b->next)
                        ;
                b->next = new_bucketptr(m, kvp.key, kvp.kwidth, kvp.value);
        }
}

struct kvpair *
      HMAP_kvpairs(hashmap_t *m)
{
        struct kvpair *res;
        struct bucket *b;
        u64_t i, j;

        if(m->len <= 0)
                return NULL;

        res = malloc(m->len*sizeof(struct kvpair));

        for(i = 0, j = 0; i < m->allocated; i++) {
                if (m->buckets[i].kvp.value != NULL) {
                        memcpy(&res[j++], &m->buckets[i].kvp,
                                sizeof(struct kvpair));
                        b = m->buckets[i].next;

                        for(b = m->buckets[i].next; b != NULL; b = b->next)
                                memcpy(&res[j++], &b->kvp,
                                        sizeof(struct kvpair));
                }
        }
        return res;
}

void  HMAP_remake(hashmap_t *m, u64_t len, hash_f hashf)
{
        struct kvpair *entries;
        u64_t i, old_len;

        entries = HMAP_kvpairs(m);

        if(entries == NULL)
                return;

        old_len = m->len;
        /**
         * free the current map without freeing the keys and values themselves.
         **/
        HMAP_free_map(&m);

        m = HMAP_new(m->vwidth, len, hashf);
        for(i = 0; i < old_len; i++)
                HMAP_add_kvpair(m, entries[i]);

        free(entries);
}

void  HMAP_rehash(hashmap_t *m, hash_f hashf)
{
        HMAP_remake(m, m->len, hashf);
}

void  HMAP_resize(hashmap_t *m, u64_t len)
{
        HMAP_remake(m, len, m->hashf);
}
