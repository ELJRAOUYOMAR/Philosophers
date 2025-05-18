#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

int nbre = 0;
pthread_mutex_t mutex;

void *func1(void *arg);
void *func2(void *arg);

int main()
{
    pthread_t t1, t2;

    pthread_create(&t1, NULL, func1, NULL);
    pthread_create(&t2, NULL, func2, NULL);

    pthread_join(t1, NULL);
    pthread_join(t2, NULL);

    printf("Final counter value: %d\n", nbre);

    pthread_mutex_destroy(&mutex);
    return 0;
}

void *func1(void *arg)
{
    for (int i = 0; i < 1000000; i++)
    {
        pthread_mutex_lock(&mutex);
        nbre++;
        pthread_mutex_unlock(&mutex);
    }
}

void *func2(void *arg)
{
    for (int i = 0; i < 1000000; i++)
    {
        pthread_mutex_lock(&mutex);
        nbre++;
        pthread_mutex_unlock(&mutex);
    }
}