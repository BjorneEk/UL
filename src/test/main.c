


#include "../UL.h"
#include <stdio.h>

int main(int argc, char const *argv[])
{
  printf("TESTING\n");
  /*int ints[] = {1,2,3,4,5,10};
  double floats[] = {1.0,2.0,3.0,4.0,5.0,3.14159264};
  char * res;
  res = iarrtos(ints, 6);
  printf("result1: %s\n", res);
  free(res);
  res = farrtos(floats, 6);
  printf("result2: %s\n", res);
  free(res);*/

  char * icsv = "1, 2, 3, 4, 5, 6,";
  char * fcsv = "1.0, 2.0, 3.0, 4.0, 5.0, 3.1415926535,";
  int * res, cnt, i;
  f64_t * res2;
  cnt = CSV_iarr(&res, icsv, ',');
  for(i=0;i<cnt;i++)printf("%i, ", res[i]);
  printf("size: %i\n", cnt);
  cnt = CSV_farr(&res2, fcsv, ',');
  for(i=0;i<cnt;i++)printf("%f, ", res2[i]);
  printf("size: %i\n", cnt);
  return 0;
}
