#include <stdio.h>
#include <pthread.h>
#define N 5


int first_fact = 1;
int second_fact = 1;

void *first_operation(__attribute__((unused))void *arg);
void *second_operation(__attribute__((unused))void *arg);

int main()
{
    pthread_t t1, t2;
    int fact = 1;
    pthread_create(&t1, NULL, first_operation, NULL);
    pthread_join(t1, NULL);

    pthread_create(&t2, NULL, second_operation, NULL);
    pthread_join(t2, NULL);
    
    fact = first_fact * second_fact;
    printf("the factorial of %d is %d\n", N, fact);
    return 0;
}

void *first_operation(__attribute__((unused))void *arg)
{
    for (int i = N / 2; i > 1; i--)
    {
        first_fact *= i;
    }
    return NULL;
}

void *second_operation(__attribute__((unused))void *arg)
{
    for (int i = N; i > N / 2; i--)
    {
        second_fact *= i;
    }
    return NULL;
}
