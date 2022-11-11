/*==========================================================*
 *
 * @author Gustaf Franzén :: https://github.com/BjorneEk;
 *
 * Util-Library variable length array
 *
 *==========================================================*/

#ifndef _UL_VLA_H_
#define _UL_VLA_H_

#include "types.h"
#define VLA_DOUBLE_IN_SIZE (-1)


typedef struct vla {

        /**
         * the array itself.
         **/
        void *data;

        /**
         * the width in bytes of a single entry.
         **/
        u64_t width;
        /**
         * number of elements currently in the array
         **/
        u64_t len;

        /**
         * currently allocated space in bytes
         **/
        u64_t _allocated;

        /**
         * when the array needs expanding it does so by this amount.
         * if negative it will instead double the currently allocated size.
         **/
        i64_t expandsize;
} vla_t;

/**
 * create a new vla array
 * @width the size in bytes of a single element.
 * @expandsize, size in no elements to expand by
 *        when expanding, can be VLA_DOUBLE_IN_SIZE
 * @len the initial lenght to be allocated
 **/
vla_t * VLA_new(u64_t width, i64_t expandsize, u64_t len);
/**
 * free the vla_t * and the data it stores
 **/
void    VLA_free(vla_t * self);

/**
 * empty the array, not same ass free
 **/
void    VLA_clear(vla_t * self);

/**
 * expand the array by @size * @self->width ie make room for @size more elements
 **/
void    VLA_expand(vla_t * self, u64_t size);

/**
 * returns the space left in the array in number of elements
 **/
u64_t   VLA_space(vla_t * self);

/**
 * returns true if the array is fully populated
 **/
bool    VLA_isfull(vla_t * self);

/**
 * returns the size in number of elementr the vla expands with when expanding
 */
u64_t   VLA_get_expandsize(vla_t * self);

/**
 * insert data to self at index i, return true if it was removed
 **/
bool    VLA_insert(vla_t * self, u64_t i, void *data);

/**
 * insert c elements from data to self at index i, return true if it was removed
 **/
bool    VLA_insertn(vla_t * self, u64_t i, u64_t cnt, void * data);

/**
 * append data to self, return true if it was removed
 **/
bool    VLA_append(vla_t * self, void *data);

/**
 * append c elements from data to self, return true if it was removed
 **/
bool    VLA_appendn(vla_t * self, u64_t c, void *data);

/**
 * prepend data to self, return true if it was removed
 **/
bool    VLA_prepend(vla_t * self, void *data);

/**
 * prepend c elements from data to self, return true if it was removed
 **/
bool    VLA_prependn(vla_t * self, u64_t c, void *data);

/**
 * remove the element at index i in self, return true if it was removed
 **/
bool    VLA_remove(vla_t * self, u64_t i);

/**
 * if e exists in self return its index else return -1
 **/
i64_t   VLA_indexof(vla_t * self, const void *e, compare_f cmp);

#endif /* _UL_VLA_H_ */
