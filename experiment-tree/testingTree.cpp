#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include<iostream>
#include<vector>
#include<map>
using namespace std;


void spawnProcessTree(int cnt)
{
    if(cnt==2) return;

    for(int i=0;i<3;i++) 
    {
        if(fork() == 0)
        {
            cout<<"child #"<<getpid()<<" of parent #"<<getppid()<<endl;
            int parentId=getppid();
            int childId=getpid();

            spawnProcessTree(cnt+1);
            exit(0);
        }
    }
    for(int i=0;i<3;i++) 
    wait(NULL);
}

int main()
{
    spawnProcessTree(0);
}