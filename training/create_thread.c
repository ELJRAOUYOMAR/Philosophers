#include <stdio.h>
#include <pthread.h>
#include <unistd.h>

/*
 * pthread_create: spawn(create) new threads.
 * 
 * thread: Pointer to a pthread_t variable to store the thread ID.
 *
 * prototype: int pthread_create(pthread_t *thread, const pthread_attr_t *attr,
                   void *(*start_routine)(void *), void *arg);
 * @attr: Pointer to a pthread_attr_t structure for thread attributes (e.g., stack size, priority). Use NULL for default attributes.
 * @start_routine: Pointer to the function the thread will execute. It must return void * and take a void * argument.
 * @arg: Argument passed to the start_routine.
 * 
 * Return : Returns 0 on success, or an error code on failure.
*/
void *thread_function(void *arg);

int main()
{
    pthread_t thread_id;
    char *msg = "this is a thread";

    // create new thread
    int res = pthread_create(&thread_id, NULL, thread_function, (void *)msg);
    if (res != 0)
    return (fprintf(stderr, "thread creation failed%d\n", res), 1);

    // main thread does some works
    for (int i = 0; i < 3; i++)
    {
        printf("Main thread: working... (Iteration %d)\n", i + 1);
        sleep(1);
    }

    // wait for the thread to finish
    res = pthread_join(thread_id, NULL);
    printf("res in joined = %d\n", res);
    if (res != 0)
    return (fprintf(stderr, "thread join failed%d\n", res), 1);

    printf("thread has finished, main thead exiting.\n");
    return 0;
}

void *thread_function(void *arg)
{
    char *msg = (char *)arg;
    for (int i = 0; i < 3; i++)
    {
        printf("thread says: %s(Iteration %d)\n", msg, i + 1);
        sleep(1); // simulate some work
    }
    return NULL; 
}