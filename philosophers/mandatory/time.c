#include "includes/philo.h"

/**
 * get_time - get current timestamp in milliseconds
 * 
 * Return:  Current timestamp in milliseconds, or -1 on error
 */
long long get_time()
{
    struct timeval tv;

    if (gettimeofday(&tv, NULL))
        return (-1);
    return ((tv.tv_sec * 1000) + (tv.tv_usec / 1000));
}

/**
 * time_diff - calculate time difference in milliseconds
 * 
 * @past: Past timestamp
 * @present: Present timestamp
 * Return: Time difference in milliseconds
 */
long long	time_diff(long long past, long long present)
{
	return (present - past);
}

/**
 * precise_sleep - sleep for a precise amount of time
 * 
 * @time_ms: Time to sleep in milliseconds
 * 
 * Return: nothing(void)
 */

void precise_sleep(long long time_sleep_in_ms)
{
    long long start;
    long long current;

    start = get_time();
    if (start == -1)
        return ;
    while (1)
    {
        current = get_time();
        if (current == -1 || time_diff(start, current) >= time_sleep_in_ms)
            break ;
        usleep(500); // sleep in short for more precision    
    }

}