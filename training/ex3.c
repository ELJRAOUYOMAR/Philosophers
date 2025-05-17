#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#define N 5


void *ping_a(__attribute__((unused))void *arg);
void *ping_b(__attribute__((unused))void *arg);

int main()
{
    pthread_t t1, t2;

    pthread_create(&t1, NULL, ping_a, NULL);
    pthread_join(t1, NULL);

    pthread_create(&t2, NULL, ping_b, NULL);
    pthread_join(t2, NULL);

    return 0;
}

void *ping_a(__attribute__((unused))void *arg)
{
    for (int i = 0; i < N; i++)
    {
        printf("Ping form A");
        sleep(1);
    }
    return NULL;
}

void *ping_b(__attribute__((unused))void *arg)
{
    for (int i = 0; i < N; i++)
    {
        printf("Ping form B");
        sleep(1);
    }
    return NULL;
}