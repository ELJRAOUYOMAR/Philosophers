#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

int nbrs[] = {1, 0, 4, 5, 1};
int sum1 = 0;
int sum2 = 0;

void *half_one(void *arg);
void *half_two(void *arg);

int main()
{
    pthread_t id1, id2;
    int final_some = 0;
    if ((pthread_create(&id1, NULL, half_one, NULL) != 0))
    {
        printf("Error: creating the first thread");
        return 1;
    }
    if (pthread_join(id1, NULL) != 0)
    {
        printf("Error: joining the first thread");
        return 1;
    }

    if ((pthread_create(&id2, NULL, half_two, NULL) != 0))
    {
        printf("Error: creating the first thread");
        return 1;
    }
    if (pthread_join(id2, NULL) != 0)
    {
        printf("Error: joining the first thread");
        return 1;
    }
    final_some = sum1 + sum2;
    printf("Some of the elements is: %d", final_some);
}

void    *half_one(__attribute__((unused))void *arg)
{
    for (int i = 0; i < (sizeof(nbrs) / sizeof(nbrs[0])) / 2; i++)
    {
        sum1 += nbrs[i];
    }
}

void    *half_two(__attribute__((unused))void *arg)
{
    for (int i = ((sizeof(nbrs) / sizeof(nbrs[0])) / 2); i < sizeof(nbrs) / sizeof(nbrs[0]); i++)
    {
        sum2 += nbrs[i];
    }
}