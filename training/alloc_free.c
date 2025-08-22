#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

pthread_mutex_t lock;
void *routine1(void *arg)
{
    int **x = (int **)arg;

    pthread_mutex_lock(&lock);
    *x = malloc(sizeof(int) * 5);
    printf("Thread 1: allocated memory\n");
    pthread_mutex_unlock(&lock);

    return NULL;
}

void *routine2(void *arg)
{
    int **x = (int **)arg;
    pthread_mutex_lock(&lock);
    if (*x)
    {
        free(*x);
        *x = NULL;
        printf("Thread2: freed memory\n");
    }
    pthread_mutex_unlock(&lock);

    return NULL;
}

int main()
{
    pthread_t t1, t2;
    int *x = NULL;

    pthread_mutex_init(&lock, NULL);

    pthread_create(&t1, NULL, routine1, &x);
    pthread_create(&t2, NULL, routine2, &x);
    
    pthread_join(t1, NULL);
    pthread_join(t2, NULL);

    pthread_mutex_destroy(&lock);
    return 0;
}