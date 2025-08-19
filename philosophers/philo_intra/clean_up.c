#include "includes/philo.h"

void clean_up(t_data *data)
{
    int i;

    if (data->forks)
    {
        i = 0;
        while (i < data->num_philos)
        {
            pthread_mutex_destroy(&data->forks[i]);
            i++;
        }
        free(data->forks);
    }
    pthread_mutex_destroy(&data->write_lock);
	pthread_mutex_destroy(&data->meal_lock);
	pthread_mutex_destroy(&data->end_lock);
    if (data->philosophers)
        free(data->philosophers);
}

void join_threads(t_data *data)
{
    int i;

    i = 0;
    while (i < data->num_philos)
    {
        pthread_join(data->philosophers[i].thread_id, NULL);
        i++;
    }
}
