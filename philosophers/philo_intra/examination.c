#include "includes/philo.h"

void *monitor_routine(void *arg)
{
    int i;
    t_data  *data;

    data = (t_data *) arg;
    while (!simulation_finished(data))
    {
        i = 0;
        if (check_death(data, &i) || check_each_philo_eat(data))
        {
            pthread_mutex_lock(&data->end_lock);
            data->simulation_end = 1;
            pthread_mutex_unlock(&data->end_lock);
        }
        usleep(data->time_to_die / 10);
    }
    return (NULL);
}

int	check_death(t_data *data, int *i)
{
    long long   currect_time;
    long long   time_since_meal;

    while (*i < data->num_philos)
    {
        pthread_mutex_lock(&data->meal_lock);
        currect_time = get_time();
        if (currect_time == -1)
        {
            pthread_mutex_unlock(&data->meal_lock);
            return (1);
        }
        time_since_meal = time_diff(data->philosophers[*i].last_meal_time,
            currect_time);
        if (time_since_meal > data->time_to_die)
        {
            pthread_mutex_unlock(&data->meal_lock);
            print_status(data, data->philosophers[*i].id, DIED);
            return (1);
        }
        pthread_mutex_unlock(&data->meal_lock);
        (*i)++;
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