#include <stdio.h>  // Для printf
#include <time.h>   // Для time, ctime

int main (void) 
{
   time_t ttime; 
   struct tm *tmp;
   char s1[11];
   ttime = time (NULL);
   tmp = localtime(&ttime);
   strftime(s1, 11, "%F", tmp);
   printf("%s\n", s1);
   //86400 - 1 сутки
   return 0;
}
