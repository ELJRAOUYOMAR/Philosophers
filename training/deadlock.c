#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

#define THREAD_NUMBER 8 
pthread_mutex_t mutexFuel;
pthread_mutex_t mutexWater;
int fuel = 50;
int water = 10;

void *routine(void *arg);

int main()
{
    int i;
    pthread_t th[THREAD_NUMBER];
    
    pthread_mutex_init(&mutexFuel, NULL);
    pthread_mutex_init(&mutexWater, NULL);
    printf("first value of fuel: %d\n", fuel);

    for (i = 0; i < THREAD_NUMBER; i++)
    {
        if (pthread_create(&th[i], NULL, routine, NULL))
        {
            printf("problem when create the thread %d\n", i);
            return 1;
        }
    }
    for (i = 0; i < THREAD_NUMBER; i++)
    {
        if (pthread_join(th[i], NULL))
        {
            printf("join problem in thread %d\n", i);
            return 1;
        }
    }
    printf("Fuel = %d\n", fuel);
    pthread_mutex_destroy(&mutexFuel);
    pthread_mutex_destroy(&mutexWater);
    return 0;
}

void *routine(void *arg)
{
    if (rand() % 2 == 0)
    {
        pthread_mutex_lock(&mutexFuel);
        pthread_mutex_lock(&mutexWater);
    }
    else
    {
        pthread_mutex_lock(&mutexWater);
        pthread_mutex_lock(&mutexFuel);
    }
    fuel += 50;
    water += 10;
    printf("Incremented fuel to %d and water to %d\n", fuel, water);
    pthread_mutex_unlock(&mutexFuel);
    pthread_mutex_unlock(&mutexWater);
    sleep(1);
    return NULL;
}