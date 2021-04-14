#include <stdio.h>  // Для printf
#include <time.h>   // Для time, ctime

enum
{
    Y = 1925;
    M = 10;
    D = 7
}

int main (void) 
{
   time_t ttime; 
   struct tm *tmp, *nul;
   nul->tm_year = Y;
   nul->tm_mon = M - 1;
   nul->tm_mday = D;
   scanf("%d", &(tmp->tm_year));
   scanf("%d", &(tmp->tm_mon));
   scanf("%d", &(tmp->tm_mday)); 
   tmp->tm_mon--;
   ttime = mktime(tmp) - mktime(nul);
   ttime = difftime(ttime); 
   printf("%d\n", ttime);
   //86400 - 1 сутки
   return 0;
}