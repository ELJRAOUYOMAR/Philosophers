#include <stdio.h>
#include <unistd.h>
#include <pthread.h>
#include <stdlib.h>


int balance = 1000;
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

void *person1(void *arg);
void *person2(void *arg);

int main()
{
    pthread_t t1, t2;

    pthread_create(&t1, NULL, person1, NULL);
    pthread_create(&t2, NULL, person2, NULL);

    pthread_join(t1, NULL);
    pthread_join(t2, NULL);
    
    pthread_mutex_destroy(&mutex);
    return 0;
}

void *person1(__attribute__((unused))void *arg)
{
    pthread_mutex_lock(&mutex);
    if (balance >= 700)
    {
        balance -= 700;
        printf("Thread 1: Withdrawal successful. New balance = %d\n", balance);
    }
    else 
    {
        printf("Thread 1: Withdrawal failed. Not enough funds.\n");
        exit(1);
    }
    pthread_mutex_unlock(&mutex);
}

void *person2(__attribute__((unused))void *arg)
{
    pthread_mutex_lock(&mutex);
    if (balance >= 700)
    {
        balance -= 700;
        printf("Thread 2: Withdrawal successful. New balance = %d\n", balance);
    }
    else 
    {
        printf("Thread 2: Withdrawal failed. Not enough funds.\n");
        exit(1);
    }
    pthread_mutex_unlock(&mutex);
}