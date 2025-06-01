# Philosophers

## Definition
The Philosophers project (42 school) is a coding exercise where students implement a solution to the Dining Philosophers Problem in C, using threads, processes, mutexes, or semaphores to manage shared resources and prevent deadlock or starvation in a concurrent simulation of philosophers eating and thinking.

```
• This project is to be coded in C, following the 42 Norm. Any leak, crash, undefined
behavior or norm error means 0 to the project.

• A number of philosophers are sitting at a round table doing one of three things:
eating, thinking or sleeping.

• While eating, they are not thinking or sleeping, while sleeping, they are not eating
or thinking and of course, while thinking, they are not eating or sleeping.

• The philosophers sit at a circular table with a large bowl of spaghetti in the center.
• There are some forks on the table.

• As spaghetti is difficult to serve and eat with a single fork, it is assumed that a
philosopher must eat with two forks, one for each hand.

• The philosophers must never be starving.

• Every philosopher needs to eat.

• Philosophers don’t speak with each other.

• Philosophers don’t know when another philosopher is about to die. 

• Each time a philosopher has finished eating, he will drop his forks and start sleeping.

• When a philosopher is done sleeping, he will start thinking.

• The simulation stops when a philosopher dies.

• Each program should have the same options: number_of_philosophers time_to_die
time_to_eat time_to_sleep [number_of_times_each_philosopher_must_eat]

◦ number_of_philosophers: is the number of philosophers and also the number
of forks

◦ time_to_die: is in milliseconds, if a philosopher doesn’t start eating ’time_to_die’
milliseconds after starting his last meal or the beginning of the simulation, it
dies

◦ time_to_eat: is in milliseconds and is the time it takes for a philosopher to
eat. During that time he will need to keep the two forks.

◦ time_to_sleep: is in milliseconds and is the time the philosopher will spend
sleeping.

◦ number_of_times_each_philosopher_must_eat: argument is optional, if all
philosophers eat at least ’number_of_times_each_philosopher_must_eat’ the
simulation will stop. If not specified, the simulation will stop only at the death
of a philosopher.

• Each philosopher should be given a number from 1 to ’number_of_philosophers’.

• Philosopher number 1 is next to philosopher number ’number_of_philosophers’.
Any other philosopher with number N is seated between philosopher N - 1 and
philosopher N + 1

• Any change of status of a philosopher must be written as follows (with X replaced
with the philosopher number and timestamp_in_ms the current timestamp in milliseconds)
◦ timestamp_in_ms X has taken a fork  
◦ timestamp_in_ms X is sleeping  
◦ timestamp_in_ms X is thinking  
◦ timestamp_in_ms X died  

• The status printed should not be scrambled or intertwined with another philosopher’s status.

• You can’t have more than 10 ms between the death of a philosopher and when it
will print its death.

• Again, philosophers should avoid to die!
```

## keys concepts
- each process can have multiple threads of execution.
- Each thread is executing the same program code and shares the same data area and heap.
- each thread has it own stack containing local variables and function call linkage information.
- Threads can communicate with each other via the global variables that they share.

## Race condition
A race condition happens when two or more processes or threads access shared data at the same time, and the final outcome depends on the timing of their execution. If not handled properly, it can lead to unexpected or incorrect behavior.
#### Example:
```C
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
```
- ✅ No data race: All shared access is synchronized.

- ⚠️ Still a race condition: Outcome (who wins) depends on timing.

## Data race
A data race is a specific type of race condition where multiple threads access the same memory location simultaneously, with at least one thread performing a write operation, and there's no proper synchronization.

#### Example
```C
#include <stdio.h>
#include <pthread.h>

int shared = 0;

void* increment(void* arg) {
    for (int i = 0; i < 100000; ++i)
        shared++;  // Read-modify-write with no synchronization
    return NULL;
}

int main() {
    pthread_t t1, t2;
    pthread_create(&t1, NULL, increment, NULL);
    pthread_create(&t2, NULL, increment, NULL);
    pthread_join(t1, NULL);
    pthread_join(t2, NULL);
    printf("shared = %d\n", shared);
    return 0;
}
```
- ❗ Data Race: Both threads modify shared without synchronization (e.g., mutex).
- 🔥 Undefined behavior: Final value may vary each run.

## deadlock
A deadlock occurs when two or more threads are waiting on each other to release resources, but none of them ever do, so all the threads are stuck forever.
#### 🧵 Deadlock in Simple Terms
Imagine:
- Thread A holds Lock 1 and wants Lock 2
- Thread B holds Lock 2 and wants Lock 1
Now both threads wait forever for each other. That’s a deadlock.