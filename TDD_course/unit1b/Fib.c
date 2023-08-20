///@file Fib.c

#include "Fib.h"

#define     FIB_FIRST_BAD_ELEMENT     (46)
/*!Get element of the Fibonacci series*/
int Fibonacci_GetElement(int num)
{
   int i;
   int first  = 1;
   int second = 1;
   int next   = 1;

   if (num <= 0 || num >= FIB_FIRST_BAD_ELEMENT)
     return 0;
   for (i = 2; i <= num; i++)
   {
     next = first + second;
     first = second;
     second = next;
   }

   return next;
}


int Fibonacci_IsInSequence(int num)
{
   int i;
   int first  = 1;
   int second = 1;
   int next   = 1;

   if (num <= 0)
     return 0;
   if (num == 1)
     return 1;
   for (i = 2; ((next > num) || (next <= 0)); i++)
   {
     next = first + second;
     if (next == num)
         return 1;
     first = second;
     second = next;
   }

   return 0;
}
