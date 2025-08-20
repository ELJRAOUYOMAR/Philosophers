#include "philo.h"

int start_simulation(t_data *data)
{
    int i;
    pthread_t   monitor;
    
    data->start_time = get_time();
    if (data->start_time == -1)
        return (1);
    i = 0;
    while (i < data->num_philos)
    {
        data->philosophers[i].last_meal_time = data->start_time;
        i++;
    }
    i = 0;
    while (i < data->num_philos)
    {
        if (pthread_create(&data->philosophers[i].thread_id, NULL,
            philosopher_routine, &data->philosophers[i]))
        {
            pthread_mutex_lock(&data->end_lock);
            data->simulation_end = 1;
            pthread_mutex_unlock(&data->end_lock);
            return (1);
        }
        i++;
    }
    if (pthread_create(&monitor, NULL, monitor_routine, data))
    {
        pthread_mutex_lock(&data->end_lock);
        data->simulation_end = 1;
        pthread_mutex_unlock(&data->end_lock);
        return (1);
    }
    pthread_join(monitor, NULL);
    return (0);
}

int simulation_finished(t_data *data)
{
    int end;

    pthread_mutex_lock(&data->end_lock);
    end = data->simulation_end;
    pthread_mutex_unlock(&data->end_lock);
    return (end);
}