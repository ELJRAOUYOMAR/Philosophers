#include "philo.h"

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
    pthread_mutex_lock(&data->end_lock);
    if (!data->simulation_end)  // Double-check to avoid duplicate death messages
    {
        data->simulation_end = 1;
        current_time = get_time();
        if (current_time != -1)
        {
            printf("%lld %d %s\n",
                time_diff(data->start_time, current_time), id, DIED);
        }
    }
    pthread_mutex_unlock(&data->end_lock);
    pthread_mutex_unlock(&data->write_lock);
}

int	check_death(t_data *data)
{
    int i;
    long long current_time;
    long long time_since_meal;
    long long last_meal;

    i = 0;
    while (i < data->num_philos)
    {
        pthread_mutex_lock(&data->meal_lock);
        last_meal = data->philosophers[i].last_meal_time;
        pthread_mutex_unlock(&data->meal_lock);
        current_time = get_time();
        time_since_meal = time_diff(last_meal, current_time);
        if (current_time == -1)
            return (1);
        
        // Philosopher dies if time since last meal > time_to_die
        // Use > instead of >= to give philosophers the full time_to_die duration
        if (time_since_meal >= data->time_to_die)
        {
            printf_death(data, data->philosophers[i].id);
            return (1);
        }
        i++;
    }
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