#include <stdio.h>
#include <unistd.h>
#include <pthread.h>
#include <stdlib.h>

pthread_mutex_t mutex;
int nbre = 0;

void *routine(__attribute__((unused))void *arg)
{
    for (int i = 0; i < 1000000; i++)
    {
        pthread_mutex_lock(&mutex);
        nbre++;
        pthread_mutex_unlock(&mutex);
    }
    return NULL;
}
int main()
{
    pthread_t t[4];
    pthread_mutex_init(&mutex, NULL);
    for (int i = 0; i < 4; i++)
    {
        if (pthread_create(&t[i], NULL, routine, NULL) != 0)
        {
            perror("Failed to create thread");
            return 1;
        }
        printf("thread %d has started\n", i + 1);
    }

    for (int i = 0; i < 4; i++)
    {
        if (pthread_join(t[i], NULL))
        {
            perror("join Error");
            return 1;
        }
        printf("Thread %d has finished execution\n", i + 1);
    }

    pthread_mutex_destroy(&mutex);
    printf("nbre = %d", nbre);

    return 0;
}