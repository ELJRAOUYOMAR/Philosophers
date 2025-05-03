#include <pthread.h>
#include <stdio.h>
#include <errno.h>
#include <unistd.h>

void* thread_func(void* arg) {
    printf("Thread running\n");
    while (1) {
        sleep(1); // Cancellation point
    }
    return NULL;
}

int main() {
    pthread_t thread;
    if (pthread_create(&thread, NULL, thread_func, NULL) != 0) {
        perror("pthread_create failed");
        return 1;
    }

    sleep(2); // Let thread run briefly
    if (pthread_cancel(thread) != 0) {
        perror("pthread_cancel failed");
        return 1;
    }

    if (pthread_join(thread, NULL) != 0) {
        perror("pthread_join failed");
        return 1;
    }

    printf("Thread canceled\n");
    return 0;
}