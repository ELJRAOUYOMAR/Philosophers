#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include <stdlib.h>

/*
    Race condition
*/
int nbre = 0;

void* routine(__attribute__((unused))void *arg)
{
    for (int i = 0; i < 1000000; i++)
    {
        nbre++;
    }
    return NULL;
}

int main()
{
    pthread_t thread1, thread2;

    if (pthread_create(&thread1, NULL, routine, NULL))
        return 1;
    if (pthread_create(&thread2, NULL, routine, NULL))
        return 1;

    if (pthread_join(thread1, NULL))
        return 1;
    if (pthread_join(thread2, NULL))
        return 1;
    
    printf("nbre = %d\n", nbre); // the first and second routine access at the same memory and change on it in the same time, that is exactly the race condition
    return 0;
}
