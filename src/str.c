
/*==========================================================*
 *
 * @author Gustaf Franzén :: https://github.com/BjorneEk;
 *
 * function defenitions for the util.h header
 *
 *==========================================================*/

#include "str.h"
#include "assert.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>


inline bool is_ascii(i32_t i)
{
        return ((31 < i) && (127 > i));
}

u32_t nbr_of_digits(u64_t n, u32_t base)
{
        u32_t res;
        for (res = 0; n != 0; n /= base, ++res);
        return res;
}

i64_t indexof(const char * str, char ch)
{
        const char * c;

        for(c = str; *c != '\0' && *c != ch; c++);
        return c-str;
}

void moveto(char **c, char ch)
{
        *c = *c + indexof(*c, ch);
}

/**
 * function that append a float to the end of a string
 **/
char * append_float(char * buff, f64_t f, i32_t blen)
{
        char * c;
        i32_t pchars;

        for(c = buff; *c != '\0'; c++);

        c += snprintf(c, blen, "%f", f);

        return c;
}


char * WUNUSED iarrtos(i32_t * data, i64_t length)
{
        char * res, *c;
        i32_t ccnt, i;

        if(!length) return NULL;

        for(i = 0, ccnt = 0; i < length; i++)
                ccnt += nbr_of_digits(data[i], 10);

        res = malloc(sizeof(char) * (((length - 1) * 2) + ccnt +1));
        assertf(res != NULL, "%s", "Out of memory (iarrtos)");

        for(i = 0, c = res; i < length; i++) {
                c += sprintf(c, "%i", data[i]);

                if(i != length-1)
                        *c++ = ',', *c++ = ' ';
        }
        *c = '\0';
        return res;
}

char * WUNUSED farrtos(f64_t * data, i64_t length)
{
        char * res, *c;
        i32_t i, pchars;

        res = malloc(10 * length * sizeof(char));
        assertf(res != NULL,"%s", "Out of memory (farrtos)");
        memset(res, '\0', 10 * length * sizeof(char));

        for(i=0,c=res;i<length;i++) {
                c = append_float(c, data[i], 10*length);

                if(i != length-1)
                        *c++ = ',', *c++ = ' ';
        }
        return res;
}

/**
 * returns the number of words in a string where words are separated by delim
 **/
u64_t strcnt(const char * buff, char delim)
{
        const char * c;
        u64_t res;

        for(c = buff, res = 0; *c != '\0'; res += (*c == delim), c++);
        res += (*--c != delim);
        return res;
}

i64_t CSV_iarr(i32_t ** res, char * data, char del)
{
        char *c;
        i64_t cnt, i;

        cnt = strcnt(data, del);

        *res = malloc(cnt * sizeof(i32_t));
        assertf(*res != NULL,"%s", "Out of memory (CSV_iarr)");

        for(c=data,i=0;*c!='\0'&&i<cnt;c++)
                if(*c!=del&&!isspace(*c)) {
                        (*res)[i++] = atoi(c);
                        moveto(&c, del);
                }
        return cnt;
}


i64_t CSV_farr(f64_t ** res, char * data, char del)
{
        char *c, tmp[100];
        i64_t cnt, i;

        cnt = strcnt(data, del);

        *res = malloc(cnt * sizeof(f64_t));
        assertf(*res != NULL, "%s", "Out of memory (CSV_farr)");

        for(c=data,i=0;*c!='\0'&&i<cnt;c++)
                if(*c!=del&&!isspace(*c)) {
                        (*res)[i++] = atof(c);
                        moveto(&c, del);
                }
        return cnt;
}
