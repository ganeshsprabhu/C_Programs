/* Generated by Frama-C */
#include "errno.h"
#include "stdarg.h"
#include "stddef.h"
#include "stdio.h"
int p(int x, int y)
{
  int output = 4;
  int count = 0;
  while (count < 7) {
    if (x > 10) 
      if (y == 1) output = 2; else output = 1;
    else 
      /*@ assert Eva: signed_overflow: output + 1 ≤ 2147483647; */
      output ++;
    count ++;
  }
  /*@ assert output ≤ 10; */ ;
  return output;
}

