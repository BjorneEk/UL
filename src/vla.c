/*==========================================================*
 *
 * @author Gustaf Franzén :: https://github.com/BjorneEk;
 *
 * Util-Library variable length array functions
 *
 *==========================================================*/
#include "vla.h"
#include "assert.h"
#include "macro.h"
#include "math.h"
#include <string.h>


#define IDX(vla, i) ((vla)->data + ((i) * (vla)->width))


vla_t * VLA_new(u64_t width, i64_t expandsize, u64_t len)
{
        vla_t * new;

        new = malloc(sizeof(vla_t));
        assert(new != NULL);

        new->expandsize = expandsize;
        new->_allocated =        len;
        new->width      =      width;
        new->len        =          0;
        new->data       = calloc(len, width);

        assert_to(new->data != NULL, err);

        return new;
err:
        free(new);
        return NULL;
}


void VLA_free(vla_t * self)
{
        if (self->data != NULL)
                free(self->data);

        if (self       != NULL)
                free(self);
}

void VLA_clear(vla_t * self)
{
        self->len = 0;
}

void VLA_expand(vla_t * self, u64_t size)
{
        void *data;
        u64_t new_size;

        new_size = (size + self->_allocated);
        data = realloc(self->data, self->width * new_size);
        assert(data != NULL);

        self->data       =     data;
        self->_allocated = new_size;
}

u64_t VLA_space(vla_t * self)
{
        return (self->_allocated - self->len);
}

bool VLA_isfull(vla_t * self)
{
        return (VLA_space(self) <= 0);
}

ALWAYS_INLINE u64_t VLA_get_expandsize(vla_t * self)
{
        return (self->expandsize < 0) ? self->_allocated * 2 : self->expandsize;
}

bool VLA_insert(vla_t * self, u64_t i, void *data)
{
        if (i > self->len)
                return false;

        if (VLA_isfull(self))
                VLA_expand(self, VLA_get_expandsize(self));

        /**
         * move elements one step back in array to make room for the new one
         **/
        memmove(
                IDX(self, i + 1),                 /*  dest  */
                IDX(self, i    ),                 /* source */
                (self->len - i) * self->width     /*  size  */
        );

        memcpy(IDX(self, i), data, self->width);
        ++self->len;
        return true;
}

bool VLA_insertn(vla_t * self, u64_t i, u64_t cnt, void * data)
{
        u32_t j;
        if (i > self->len)
                return false;

        if (VLA_space(self) < cnt)
                VLA_expand(self, MAX(cnt, VLA_get_expandsize(self)));

        /**
         * move elements one step back in array to make room for the new one
         **/
        memmove(
                IDX(self, i + cnt),               /*  dest  */
                IDX(self, i    ),                 /* source */
                (self->len - i) * self->width     /*  size  */
        );

        memcpy(IDX(self, i), data, cnt * self->width);
        self->len += cnt;
        return true;
}

bool VLA_append(vla_t * self, void *data)
{
        return VLA_insert(self, self->len, data);
}
bool VLA_appendn(vla_t * self, u64_t c, void *data)
{
        return VLA_insertn(self, self->len, c, data);
}

bool VLA_prepend(vla_t * self, void *data)
{
        return VLA_insert(self, 0, data);
}

bool VLA_prependn(vla_t * self, u64_t c, void *data)
{
        return VLA_insertn(self, 0, c, data);
}
bool VLA_remove(vla_t * self, u64_t i)
{
        if (i >= self->len)
                return false;

        /**
         * move elements after i one step forwards in array
         **/
        memmove(
                IDX(self,i    ),                 /*  dest  */
                IDX(self,i + 1),                 /* source */
                (self->len - i) * self->width    /*  size  */
        );

        --self->len;
        return true;
}

i64_t VLA_indexof(vla_t * self, const void *e, compare_f cmp)
{
        u64_t i;

        for(i = 0; i < self->len; i++)
                if(cmp(IDX(self, i), e) == 0)
                        return i;

        return -1;
}
