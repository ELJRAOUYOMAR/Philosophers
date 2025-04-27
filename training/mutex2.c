#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>

pthread_mutex_t lock = PTHREAD_MUTEX_INITIALIZER; // static initialization, pthread_mutex_init() for dynamic initialization 

void *worker(void *arg)
{
    pthread_mutex_lock(&lock);
    printf("thread %s: in critical section\n", (char *)arg);
    while (1)
    {
        sleep(1);
    }
    pthread_mutex_unlock(&lock);
    return arg;
}

int main()
{
    pthread_t t1, t2;
    char *n1 = "n1", *n2 = "n2";
    
    pthread_create(&t1, NULL, worker, (void *)n1);
    pthread_create(&t2, NULL, worker, n2);

    sleep(2);
    pthread_join(t1, NULL);
    pthread_join(t2, NULL);

    pthread_mutex_destroy(&lock);

    return 0;
}