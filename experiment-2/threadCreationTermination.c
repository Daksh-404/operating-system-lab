/*******************/
/* program for creation and termiination of threads*/
/* for using other related function of threads*/
/*******************/
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#define NUM_THREADS	5

void *PrintHello(void *threadid)
{
    //the function the thread has to do
   long tid;
   tid = (long)threadid;

    //if you uncomment the below piece of code
    //it will detach the last thread and exit the thread without printing 
    // the line 24

   if(tid==4)
   {
       pthread_detach(pthread_self());
       printf("Detaching the last thread in the sequence!");
       pthread_exit(NULL);
   }
   printf("Hello World! It's me, thread #%ld!\n", tid);

   //exiting the thread 
   pthread_exit(NULL);
}

int main(int argc, char *argv[])
{
   pthread_t threads[NUM_THREADS];
   int rc;
   long t;
   pthread_t lastThread;
   for(t=0;t<NUM_THREADS;t++)
   {
            printf("In main: creating thread %ld\n", t);

            //creation of thread
            rc = pthread_create(&threads[t], NULL, PrintHello, (void *)t);

            // if you uncomment the below command
            //you will observe a change in the printing order.
            //basically the thread join function is like wait
            //so it blocks the next thread until the previous thread
            // is completed or exited or cancelled or terminated

            //pthread_join(threads[t],NULL);

            //error handling
            if (rc)
            {
                printf("ERROR; return code from pthread_create() is %d\n", rc);
                exit(-1);
            }

            if(t==1) lastThread=threads[t];

            if(t==3)
            {
                if(pthread_equal(lastThread,pthread_self()))
                {
                    printf("Thread #1 and #3 are equal\n");
                }
                else
                {
                    printf("Thread #1 and #3 are not equal\n");
                }
            }

            
     }

   /* Last thing that main() should do */
   pthread_exit(NULL);
}