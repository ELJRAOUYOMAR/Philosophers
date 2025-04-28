#include <stdio.h>
#include <pthread.h>
#include <unistd.h>

void *thread_running(__attribute__((unused))void *arg);

int main()
{
    pthread_t thread_id;
    pthread_attr_t attr;

    // initialize attribute thread 
    pthread_attr_init(&attr);

    // set detach state to detached
    pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_DETACHED);

    // set stack size to 1MB
    pthread_attr_setstacksize(&attr, 1024 * 1024);

    // create the thread
    if (pthread_create(&thread_id, &attr, thread_running, NULL) != 0)
    {
        printf("creation Error!\n");
        pthread_attr_destroy(&attr); // clean up before eiting
        return 1;
    }

    pthread_attr_destroy(&attr);
    
    printf("Main thread: Created detached thread with 1MB stack\n");

    // if (pthread_join(thread_id, NULL) != 0) // A detached thread runs independently and cannot be joined by another thread.
    // {
    //     printf("thread join failed\n");
    //     return 1;
    // }
    // wait for thread to run 
    sleep(1);
    printf("thread finished\n");
    return 0;
}

void *thread_running(__attribute__((unused))void *arg)
{
    // sleep(2);
    printf("thread is running...\n");
    return NULL;
}