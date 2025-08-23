#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

/*
    allocate in one thread and free the same variable in other thread 
*/
void *routine1(void *arg)
{
    int **x = (int **)arg;

    *x = malloc(sizeof(int) * 5);
    printf("Thread 1: allocated memory\n");

    return NULL;
}

void *routine2(void *arg)
{
    int **x = (int **)arg;
    if (*x)
    {
        free(*x);
        *x = NULL;
        printf("Thread2: freed memory\n");
    }

    return NULL;
}

int main()
{
    pthread_t t1, t2;
    int *x = NULL;

    pthread_create(&t1, NULL, routine1, &x);
    pthread_join(t1, NULL);
    
    pthread_create(&t2, NULL, routine2, &x);
    pthread_join(t2, NULL);

    return 0;
}