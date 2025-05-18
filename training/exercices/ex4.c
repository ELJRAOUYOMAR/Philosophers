#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>


int arr[5] = {3, 2, 1, 4, 1};


void *first_half(__attribute__((unused))void *arg);
void *second_half(__attribute__((unused))void *arg);

int main()
{
    pthread_t t1, t2;
    void *retval1, *retval2;

    pthread_create(&t1, NULL, first_half, NULL);
    pthread_create(&t2, NULL, second_half, NULL);

    pthread_join(t1, &retval1);
    pthread_join(t2, &retval2);

    for (int i = 0; i < 4; i++)
    {
        printf("%d + ", arr[i]);
    }
    int sum = *(int *)retval1 + *(int *)retval2;
    printf("%d = %d", arr[4], sum);
    frea(retval1);
    frea(retval2);
    return 0;
}

void *first_half(__attribute__((unused))void *arg)
{
    int *sum1 = malloc(sizeof(int));
    *sum1 = 0;
    for (int i = 0; i < 5 / 2; i++)
    {
        *sum1 += arr[i];
    }
    return sum1;
}

void *second_half(__attribute__((unused))void *arg)
{
    int *sum2 = malloc(sizeof(int));
    *sum2 = 0;
    for (int i = 5 / 2 ; i < 5; i++)
    {
        *sum2 += arr[i];
    }
    return sum2;
}