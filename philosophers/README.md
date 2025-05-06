# philosophers_project


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