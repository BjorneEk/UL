/*==========================================================*
 *
 * @author Gustaf Franzén :: https://github.com/BjorneEk;
 *
 * Util-Library hash functions
 *
 *==========================================================*/

#include "hash.h"

u64_t HASH_fnv_1a(const void* a, u64_t size)
{
        i64_t  nblocks;
        i64_t        i;
        u64_t     hash;
        u64_t     last;
        u8_t     *data;

        nblocks = size / 8;
        hash    = 2166136261u;
        data    = (u8_t*)a;

        for (i = 0; i < nblocks; ++i) {
                hash ^= (u64_t)data[0] << 0  | (u64_t)data[1] << 8  |
                        (u64_t)data[2] << 16 | (u64_t)data[3] << 24 |
                        (u64_t)data[4] << 32 | (u64_t)data[5] << 40 |
                        (u64_t)data[6] << 48 | (u64_t)data[7] << 56;
                hash *= 0xbf58476d1ce4e5b9; /* FNV PRIME */
                data += 8;
        }

        last = size & 0xff;
        switch (size % 8) {
        case 7:
                last |= (u64_t)data[6] << 56;
        case 6:
                last |= (u64_t)data[5] << 48;
        case 5:
                last |= (u64_t)data[4] << 40;
        case 4:
                last |= (u64_t)data[3] << 32;
        case 3:
                last |= (u64_t)data[2] << 24;
        case 2:
                last |= (u64_t)data[1] << 16;
        case 1:
                last |= (u64_t)data[0] << 8;
                hash ^= last;
                hash *= 0xd6e8feb86659fd93; /* FNV PRIME */
        }

        return hash ^ hash >> 32;
}
