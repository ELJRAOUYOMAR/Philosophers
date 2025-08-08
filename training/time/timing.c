#include <stdio.h>
#include <sys/time.h>


long long gettime()
{
    struct timeval tv;
    if (gettimeofday(&tv, NULL))
        return -1;
    return ((tv.tv_sec * 1000) + (tv.tv_usec / 1000));

}

int main()
{
    long long current_time = gettime();
    printf("%lld\n", current_time); 
}