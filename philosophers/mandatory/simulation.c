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
    // pthread_t   monitor;
    
    data->start_time = get_time();
    if (data->start_time == -1)
        return (1);
    i = 0;
    while (i < data->num_philos)
    {
        data->philosophers[i].last_meal_time = data->start_time;
        if (pthread_create(&data->philosophers[i].thread_id, NULL,
            philosopher_routine, &data->philosophers[i]))
            return (1);
        i++;
    }
    if (pthread_create(&data->monitor_thread, NULL, monitor_routine, data))
        return (1);
    // don't detach the monitor thread, we will join it later
    // if (pthread_detach(monitor))
    //     return (1);
    return (0);
}

/**
 * simulation_finished - check if simulation should end
 * 
 * @data: Pointer to simulation data
 * Return: 1 if simulation should end, 0 otherwise
 */
int simulation_finished(t_data *data)
{
    int end;

    pthread_mutex_lock(&data->end_lock);
    end = data->simulation_end;
    pthread_mutex_unlock(&data->end_lock);
    return (end);
}