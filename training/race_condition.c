#include <stdio.h>
#include <pthread.h>

int winner = -1;
pthread_mutex_t lock = PTHREAD_MUTEX_INITIALIZER;

void* try_to_win(void* arg) {
    int id = *(int*)arg;
    pthread_mutex_lock(&lock);
    if (winner == -1) {
        winner = id;
    }
    pthread_mutex_unlock(&lock);
    return NULL;
}

int main() {
    pthread_t t1, t2;
    int id1 = 1, id2 = 2;
    pthread_create(&t1, NULL, try_to_win, &id1);
    pthread_create(&t2, NULL, try_to_win, &id2);
    pthread_join(t1, NULL);
    pthread_join(t2, NULL);
    printf("winner = %d\n", winner);
    return 0;
}
