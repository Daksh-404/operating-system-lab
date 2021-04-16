#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
void exitfunc() {
printf("Called cleanup function - exitfunc()\n");
return;
}
int main() 
{
   atexit(exitfunc);
   printf("This is an example of exit() process...\n");
   _exit (0);
}