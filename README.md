# Philosophers

![philosopher dining problem](imgs/philo.png)

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
Two threads try to increase a counter:
- Thread ```A``` reads value ```5```
- Thread ```B``` reads value ```5```
- Both add ```1``` → get ```6```
- Both write ```6``` → final value is ```6```, but it should be ```7```
To prevent this, we use synchronization techniques like ```mutexes``` or ```semaphores```.

## handling Deadlock
### ``` Deadlock definition```
A deadlock in multithreading occurs when two or more threads are unable to proceed because each is waiting for a resource (e.g., a lock) that another thread holds, creating a circular dependency. No thread can progress, causing the program to hang.
Example:
- Thread 1 holds Lock A and waits for Lock B.
- Thread 2 holds Lock B and waits for Lock A. Both threads wait indefinitely, resulting in a deadlock.
```C
if (philo->id % 2 == 1)
    precise_sleep(philo->data->time_to_eat / 2);
```
This code makes odd-numbered philosophers wait a short time before starting their routine. Here's why this is important:
In the classic Dining Philosophers problem, if all philosophers try to grab their left fork simultaneously:
1. Each philosopher picks up their left fork
2. No right forks remain available for anyone
3. Everyone is stuck holding one fork and waiting for their second fork
4. This is a deadlock - ```no progress can be made```

### ```The Solution in This Code```
By delaying odd-numbered philosophers:
- Even-numbered philosophers start immediately and try to grab forks
- Odd-numbered philosophers wait briefly before attempting to grab forks
- This breaks the symmetry that could lead to deadlock
- It staggers the fork acquisition attempts
### ```Why Half of time_to_eat?```
The delay is set to half of the eating time (time_to_eat / 2), which is a reasonable value because:
- It's long enough to break synchronization
- It's short enough not to waste too much time
- It's proportional to the simulation's eating duration

### use of same part of codes
#### ```Why the meal_lock is Critical```
The meal_lock mutex protects two important variables:
- last_meal_time: Used by the monitor thread to check for starvation
- meals_eaten: Used to track when all philosophers have eaten enough
```Without this mutex:```
The monitor thread might read a partially updated timestamp
The check for "all philosophers have eaten enough" could be incorrect
These race conditions could lead to missed starvation events or premature simulation ending

```The mutex ensures these operations are atomic and properly synchronized with any threads that might be reading these values.```
