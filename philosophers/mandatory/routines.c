#include "includes/philo.h"

/**
 * Main routine for philosopher threads
 * 
 * @arg: Pointer to philosopher data (cast to t_philo *)
 * Return: NULL
 */

void *philosopher_routine(void *arg)
{
    t_philo *philo;

    philo = (t_philo *)arg;
    // if odd numbered philosopher, delay start to prevent deadlock
    if (philo->id % 2 == 1)
        precise_sleep(philo->data->time_to_eat / 2);
    while (!simulation_finished(philo->data))
    {
        take_forks(philo);
        eat(philo);
    }
}

/**
 * Handle philosopher taking forks
 * 
 * @philo: Pointer to philosopher data
 */
void take_forks(t_philo *philo)
{
    t_data  *data;

    data = philo->data;
    if (philo->left_fork_id < philo->right_fork_id)
    {
        pthread_mutex_lock(&data->forks[philo->left_fork_id]);
        print_status(data, philo->id, TAKEN_FORK);
        pthread_mutex_lock(&data->forks[philo->right_fork_id]);
        print_status(data, philo->id, TAKEN_FORK);
    }
    else
    {
        pthread_mutex_lock(&data->forks[philo->right_fork_id]);
        print_status(data, philo->id, TAKEN_FORK);
        pthread_mutex_lock(&data->forks[philo->left_fork_id]);
        print_status(data, philo->id, TAKEN_FORK);
    }
}

/**
 * eat - handle philosopher eating action
 * 
 * @philo: Pointer to philosopher data
 */

void eat(t_philo *philo)
{
    t_data *data;
    
    data = philo->data;
    pthread_mutex_lock(&data->meal_lock);
    philo->last_meal_time = get_time();
    pthread_mutex_unlock(&data->meal_lock);
    print_status(data, philo->id, EATING);
    precise_sleep(data->time_to_sleep);
    pthread_mutex_lock(&data->meal_lock);
    philo->meals_eaten++;
    pthread_mutex_unlock(&data->meal_lock);
}

