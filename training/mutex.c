#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include <stdlib.h>

/*
 - pthread_mutex_lock(&mutex);
    =>Purpose: Locks the mutex. If it's already locked by another thread, the current thread waits (blocks) until it's unlocked.
    =>Use case: Call this before accessing shared data to ensure only one thread accesses it at a time.
 - pthread_mutex_unlock(&mutex);
  =>Purpose: Unlocks the mutex so other threads can acquire it.
  =>Use case: Always called after you're done working with the shared data.
 - pthread_mutex_destroy(&mutex);
  =>Purpose: Destroys the mutex and frees any resources it was using.
  =>Use case: Call this when the mutex is no longer needed, typically before the program exits.

  - Warning⚠️: The mutex must not be locked when you destroy it.

*/

int nbre = 0;
pthread_mutex_t mutex;

void* routine(__attribute__((unused))void *arg)
{
    for (int i = 0; i < 1000000; i++)
    {
        pthread_mutex_lock(&mutex);
        nbre++;
        pthread_mutex_unlock(&mutex);
    }
    return NULL;
}

int main()
{
    pthread_t thread1, thread2;
    pthread_mutex_init(&mutex, NULL);
    if (pthread_create(&thread1, NULL, routine, NULL))
        return 1;
    if (pthread_create(&thread2, NULL, routine, NULL))
        return 1;

    if (pthread_join(thread1, NULL))
        return 1;
    if (pthread_join(thread2, NULL))
        return 1;
    pthread_mutex_destroy(&mutex);
    printf("nbre = %d\n", nbre);
    return 0;
}
