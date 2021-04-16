#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
int main()
{
    pid_t pid1, pid2, pid3, pid4;
    printf("Parent of all: %d\n", getpid());
    pid1 = fork();
    if (pid1 == 0)
    {
        printf("Child with id: %d and its Parent id: %d \n",
        getpid(), getppid());
        pid2 = fork();
        if (pid2 == 0)
        {
            printf("Child with id: %d and its Parent id: %d \n",
            getpid(), getppid());
        }
    }
    if (pid1 > 0)
    {
        pid3 = fork();
        if (pid3 == 0)
        {
            printf("Child with id: %d and its Parent id: %d \n",
            getpid(), getppid());
            pid4 = fork();
            if (pid4 == 0)
            {
                printf("Child with id: %d and its Parent id: %d \n",
                getpid(), getppid());
            }
        }
    }
    for (int i = 0; i < 3; i++)
    wait(NULL);
    return 0;
}