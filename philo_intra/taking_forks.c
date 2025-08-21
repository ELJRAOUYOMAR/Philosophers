#include "philo.h"

int take_first_fork(t_philo *philo, int first_fork)
{
    t_data *data = philo->data;
    
    pthread_mutex_lock(&data->forks[first_fork]);
    if (simulation_finished(data))
    {
        pthread_mutex_unlock(&data->forks[first_fork]);
        return (1);
    }
    print_status(data, philo->id, TAKEN_FORK);
    return (0);
}

int take_second_fork(t_philo *philo, int first_fork, int second_fork)
{
    t_data *data = philo->data;
    
    pthread_mutex_lock(&data->forks[second_fork]);
    if (simulation_finished(data))
    {
        pthread_mutex_unlock(&data->forks[second_fork]);
        pthread_mutex_unlock(&data->forks[first_fork]);
        return (1);
    }
    print_status(data, philo->id, TAKEN_FORK);
    return (0);
}

int take_forks(t_philo *philo)
{
    t_data *data = philo->data;
    int first_fork;
    int second_fork;
    
    if (simulation_finished(data))
        return (1);
    // Special case: single philosopher
    if (data->num_philos == 1)
    {
        pthread_mutex_lock(&data->forks[philo->left_fork_id]);
        if (simulation_finished(data))
        {
            pthread_mutex_unlock(&data->forks[philo->left_fork_id]);
            return (1);
        }
        print_status(data, philo->id, TAKEN_FORK);
        while (!simulation_finished(data))
            usleep(1000);
        pthread_mutex_unlock(&data->forks[philo->left_fork_id]);
        return (1);
    }
    // Determine fork order to prevent deadlock
    if (philo->left_fork_id < philo->right_fork_id)
    {
        first_fork = philo->left_fork_id;
        second_fork = philo->right_fork_id;
    }
    else
    {
        first_fork = philo->right_fork_id;
        second_fork = philo->left_fork_id;
    }
    
    if (take_first_fork(philo, first_fork))
        return (1);
    
    if (take_second_fork(philo, first_fork, second_fork))
        return (1);
    
    return (0);
}