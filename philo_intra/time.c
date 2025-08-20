#include "philo.h"

long long get_time()
{
    struct timeval tv;

    if (gettimeofday(&tv, NULL))
        return (-1);
    return ((tv.tv_sec * 1000) + (tv.tv_usec / 1000));

}
long long	time_diff(long long past, long long present)
{
	return (present - past);
}

void precise_sleep(long long time_sleep_in_ms)
{
    long long start;
    long long current;
    long long elapsed;

    start = get_time();
    if (start == -1)
        return ;
    while (1)
    {
        current = get_time();
        if (current == -1)
            break;
        elapsed = time_diff(start, current);
        if (elapsed >= time_sleep_in_ms)
            break;
        // Use different sleep strategies based on remaining time
        long long remaining = time_sleep_in_ms - elapsed;
        if (remaining > 10)
            usleep(1000);  // 1ms sleep for longer waits
        else if (remaining > 1)
            usleep(100);   // 0.1ms sleep for medium waits
        // For very short waits (≤1ms), busy wait for precision
        
        // if (current == -1 || time_diff(start, current) >= time_sleep_in_ms)
        //     break ;
        // usleep(500);   
    }

}