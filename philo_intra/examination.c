#include "includes/philo.h"

void *monitor_routine(void *arg)
{
    t_data  *data;

    data = (t_data *) arg;
    while (!simulation_finished(data))
    {
        if (check_death(data))
        {
            pthread_mutex_lock(&data->end_lock);
            data->simulation_end = 1;
            pthread_mutex_unlock(&data->end_lock);
            break;
        }
        if (check_each_philo_eat(data))
        {
            pthread_mutex_lock(&data->end_lock);
            data->simulation_end = 1;
            pthread_mutex_unlock(&data->end_lock);
            break;
        }
        usleep(1000);   // Check every 1ms for precision (within 10ms requirement)
    }
    return (NULL);
}

static void printf_death(t_data *data, int id)
{
    long long   current_time;

    pthread_mutex_lock(&data->write_lock);
    current_time = get_time();
    if (current_time != -1)
    {
        printf("%lld %d %s\n",
            time_diff(data->start_time, current_time), id, DIED);
    }
    pthread_mutex_unlock(&data->write_lock);
}
int	check_death(t_data *data)
{
    int i;
    long long   currect_time;
    long long   time_since_meal;

    i = 0;
    pthread_mutex_lock(&data->meal_lock);
    while (i < data->num_philos)
    {
        currect_time = get_time();
        if (currect_time == -1)
        {
            pthread_mutex_unlock(&data->meal_lock);
            return (1);
        }
        time_since_meal = time_diff(data->philosophers[i].last_meal_time,
            currect_time);
        // Philosopher dies if:
        // 1. Time since last meal >= time_to_die
        // 2. AND they are not currently eating
        if (time_since_meal >= data->time_to_die
            && !data->philosophers[i].is_eating)
        {
            pthread_mutex_unlock(&data->meal_lock);
            printf_death(data, data->philosophers[i].id);
            return (1);
        }
        i++;
    }
    pthread_mutex_unlock(&data->meal_lock);
    return (0);
}

int check_each_philo_eat(t_data *data)
{
    int i;
    int all_eat_enough;

    if (!data->meals_specified)
        return (0);
    pthread_mutex_lock(&data->meal_lock);
    i = 0;
    all_eat_enough = 1;
    while (i < data->num_philos)
    {
        if (data->philosophers[i].meals_eaten < data->num_meals)
        {
            all_eat_enough = 0;
            break;
        }
        i++;
    }
    pthread_mutex_unlock(&data->meal_lock);
    return (all_eat_enough);
}