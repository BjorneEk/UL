

/*==========================================================*
 *
 * @author Gustaf Franzén :: https://github.com/BjorneEk;
 *
 * Util-Library general functions
 *
 *==========================================================*/

#include "general.h"
#include <stdlib.h>

bool is_ascii(i32_t i)
{
  return ((31 < i) && (127 > i));
}

u32_t nbr_of_digits(u32_t n, u32_t base) {
	uint32_t count = 0;
	for (; n != 0; n /=base) ++count;
	return count;
}

void iarr_tos(char * res, i32_t * data, i32_t length) {
  i32_t ccnt, i;
  if(!length) return;
  for(i = 0; i < length; i++, ccnt += nbr_of_digits(data[i], 10));
  res = malloc(sizeof(char) * (((length - 1) * 2) + ccnt));

}
void iarr_toxs(char * res, i32_t * data, i32_t length) {
  if(!length) return;
}
void darr_tos(char * res, f64_t * data, i32_t length) {
  if(!length) return;
}
