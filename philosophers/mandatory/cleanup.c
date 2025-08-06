#include "includes/philo.h"

/**
 * cleanup - clean up resources (mutexes, memory)
 * 
 * @data: Pointer to simulation data
 * Return : nothing
 */
void *cleanup(t_data *data)
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
        data->forks = NULL;
    }
    pthread_mutex_destroy(&data->write_lock);
	pthread_mutex_destroy(&data->meal_lock);
	pthread_mutex_destroy(&data->end_lock);
    if (data->philosophers)
    {
        free(data->philosophers);
        data->philosophers = NULL;
    }
    return (NULL);
}

/**
 * join_threads - join all philosopher threads before exiting
 * 
 * @data: Pointer to simulation data
 */
void join_threads(t_data *data)
{
    int i;

    i = 0;
    while (i < data->num_philos)
    {
        pthread_join(data->philosophers[i].thread_id, NULL);
        i++;
    }
    // Join the monitor thread, ensures it's finished before cleanup
    pthread_join(data->monitor_thread, NULL);
}

