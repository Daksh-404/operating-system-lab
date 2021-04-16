#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
int main()
{
    int pid;
    /* fork a child process */ 
    pid = fork();
    int status=-1;
    if (pid<0){
        /* error occurred */
        exit(1);
    }

    else if (pid==0){
        /* child process */
        execlp("/bin/ls", "ls", NULL); // A new program executable is loaded into memory and executed)
        exit(2); 
    } 
    
    else {
        /* parent process */
        /* parent will wait for the child to complete */
        status=wait(NULL);
        printf("Child Completed it's process with the exit status: %d\n",status);
    }
    return 0;
}