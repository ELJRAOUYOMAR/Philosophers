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

    pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_JOINABLE);

    // set stack size to 1MB
    // pthread_attr_setstacksize(&attr, 1024 * 1024);   1M = 2^20 = 2^10(1024) * 2^10 = 
    pthread_attr_setstacksize(&attr, (1 << 10) * (1 << 10)); // 1 << 10 = 1^10

    // create the thread
    if (pthread_create(&thread_id, &attr, thread_running, NULL) != 0)
    {
        printf("creation Error!\n");
        pthread_attr_destroy(&attr); // clean up before exiting
        return 1;
    }

    // cleanup attributes
    pthread_attr_destroy(&attr);
    
    printf("Main thread: Created joinable thread with 1MB stack\n");
    
    if (pthread_join(thread_id, NULL) != 0) // wait for thread to finish
    {
        printf("thread join failed");
        return 1;
    }

    printf("Main thread: thread has finished\n");

    return 0;
}

void *thread_running(__attribute__((unused))void *arg)
{
    int i = 10;
    while (i--)
    {
        printf("thread is running...\n");
        usleep(100000);
    }
    sleep(1);
    return NULL;
}