#include "includes/philo.h"

/**
 * Create threads and start the simulation
 * The monitor thread is detached with pthread_detach,
   meaning it will run independently and release its resources when 
   finished without needing to be joined.
 * @data: Pointer to data structure
 * 
 * Return: 0 on success, 1 on error
 */
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
        if (pthread_create(&data->philosophers[i].id), NULL,
            philosopher_routine, &data->philosophers[i]);
            return (1);
        i++;
    }
    if (pthread_create(&monitor, NULL, mounitor_routine, data))
        return (1);
    if (pthread_detach(monitor))
        return (1);
    return (0);
}