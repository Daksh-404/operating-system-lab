#include <stdio.h>
#include <sys/types.h>
#include <stdlib.h>
#include <unistd.h>
int main() {
   pid_t pid, mypid, myppid;
   pid = getpid();
   printf("Before fork: Process id is %d\n", pid); 
   pid =fork();
   if (pid<0){
      perror("fork() failure\n"); return 1;
   }
   // Child process 
   if (pid == 0) {
   printf("This is child process\n\n");
   printf("Prints the current working directory:\n");
   execlp("/bin/ls", "ls", NULL); // A new program executable is loaded into memory and executed)

   mypid = getpid();
   myppid = getppid();
   printf("Process id is %d and PPID is %d\n", mypid,myppid);
   } 
   else { // Parent process
   int id=wait(NULL);
   printf("This is parent process\n"); mypid = getpid();
   myppid = getppid();
   printf("Process id is %d and PPID is %d\n", mypid,myppid); 
   printf("Newly created process id or child pid is %d\n", id);
   }
   return 0; 
}