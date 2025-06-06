#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>

void *func(void *arg)
{
    int *result = malloc(4);
    *result = 1337;
    return result;
}
int main()
{
    pthread_t thread_id;
    void *retval;

    pthread_create(&thread_id, NULL, (void *)&func, NULL);
    pthread_join(thread_id, &retval);

    if (retval != NULL)
    {
        printf("Thread returned %d\n", *(int *)retval);
        free(retval);
    }
    return 0;
}
