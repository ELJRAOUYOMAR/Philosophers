#include <stdio.h>
#include <pthread.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>



void* routine()
{
    printf("process id: %d\n", getpid());
}

int main()
{
    pthread_t t1, t2;

    if (pthread_create(&t1, NULL, &routine, NULL))
        return 1;
    if (pthread_create(&t2, NULL, &routine, NULL))
        return 1;
    
    if (pthread_join(t1, NULL))
        return 1;
    if (pthread_join(t2, NULL))
        return 1;
    
        return 0;
}
