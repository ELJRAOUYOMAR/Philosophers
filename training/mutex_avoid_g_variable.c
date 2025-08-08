#include <stdio.h>
#include <pthread.h>

int nbre = 0;
pthread_mutex_t mutex;

void* routine(void *arg)
{
    pthread_mutex_t *mutex = (pthread_mutex_t *)arg;
    for (int i = 0; i < 1000000; i++)
    {
        pthread_mutex_lock(mutex);
        nbre++;
        pthread_mutex_unlock(mutex);
    }
    return NULL;
}

int main()
{
    pthread_t thread1, thread2;
    pthread_mutex_t mutex;

    pthread_mutex_init(&mutex, NULL);
    if (pthread_create(&thread1, NULL, routine, &mutex))
        return 1;
    if (pthread_create(&thread2, NULL, routine, &mutex))
        return 1;

    if (pthread_join(thread1, NULL))
        return 1;
    if (pthread_join(thread2, NULL))
        return 1;
    pthread_mutex_destroy(&mutex);
    printf("nbre = %d\n", nbre);
    return 0;
}
