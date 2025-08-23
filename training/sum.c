#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
/*
 * Creates a thread.
 * The thread computes the sum of two integers.
 * The main thread collects the result using pthread_join’s second parameter.
 * Prints the result.
*/

void *sum(void *arg)
{
    int *nbrs = (int *)arg;
    int *res = malloc(sizeof(int));
    *res = nbrs[0] + nbrs[1];   // store result in heap
    return res;
}

int main()
{
    pthread_t t_id;
    int nbrs[2] = {3, 2};
    void *res;

    pthread_create(&t_id, NULL, sum, nbrs);
    pthread_join(t_id, &res);

    printf("the sum is %d\n", *(int *)res);
    free(res);
}