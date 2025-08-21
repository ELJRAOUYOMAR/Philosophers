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

// int precise_sleep(long long time_sleep_in_ms)
// {
//     long long    start;

//     start = get_time();
//     while ((get_time() - start) < time_sleep_in_ms)
//         usleep(50);
//     return (0);
// }