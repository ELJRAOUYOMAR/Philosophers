#include <stdio.h>
#include <unistd.h>
#include <pthread.h>


int balance = 1000;
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

void *withdraw(void *arg);

int main()
{
    pthread_t t1, t2;
    int x = 700;
    pthread_create(&t1, NULL, withdraw, &x);
    pthread_create(&t2, NULL, withdraw, &x);

    pthread_join(t1, NULL);
    pthread_join(t2, NULL);

    pthread_mutex_destroy(&mutex);

    return 0;
}

void *withdraw(void *arg)
{
    int  x = *(int *)arg;
    pthread_t tid = pthread_self(); // current thread ID

    pthread_mutex_lock(&mutex);
    if (balance >= 700)
    {
        balance -= x;
        printf("Thread %lu: Withdrawal successful. New balance = %d\n",(unsigned long)tid, balance);
    }
    else 
    {
        printf("Thread %lu: Withdrawal failed. Not enough funds.\n", (unsigned long) tid);
    }
    pthread_mutex_unlock(&mutex);
    return NULL;
}


