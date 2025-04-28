#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>

/*
 * Prototype: int gettimeofday(struct timeval *tv, struct timezone *tz)
 * @struct timeval {
    time_t tv_sec;  // Seconds since 00:00:00, 1 Jan 1970 UTC
    suseconds_t tv_usec; // additional microseconds (long int)
   } 
 * @timwzone: The second parameter was historically used for timezone information but is now obsolete and typically set to NULL
 *
 * Return: The function returns 0 on success, -1 on failure.
*/

int main()
{
    struct timeval currect_time;

    gettimeofday(&currect_time, NULL);

    int long sec = currect_time.tv_sec;
    int long microsec = currect_time.tv_usec;

    long seconds_in_day = sec % 86400; // 86400 = 24*60*60 
    printf("Currect time: %lu seconds and %lu", sec, microsec);
    printf("\ncurrent time: %luh, %lumin, %lus, %lums, %luus",
        seconds_in_day/3600, (seconds_in_day % 3600) / 60, sec % 60, microsec / 1000, microsec % 1000);
    printf("\ncurrent time: %luh, %lumin, %lus, %lums, %luus",
        seconds_in_day/3600 + 1, (seconds_in_day % 3600) / 60, sec % 60, microsec / 1000, microsec % 1000);
        
    return (0);
}