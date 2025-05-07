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
        precise_sleep(philo->data->time_to_eat);
    while (!simulation_finished(philo->data))
    {
        take_forks(philo);
        eat(philo);
        put_down_forks(philo);
        print_status(philo->data, philo->id, SLEEPING);
        precise_sleep(philo->data->time_to_sleep);
        print_status(philo->data, philo->id, THINKING);
    }
    return (NULL);
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
    if (data->num_philos == 1)
    {
        // Single philosopher: take one fork and wait to die
        pthread_mutex_lock(&data->forks[philo->left_fork_id]);
        print_status(data, philo->id, TAKEN_FORK);
        // Don't try to take a second fork; just wait
        while (!simulation_finished(data))
            usleep(100);
        pthread_mutex_unlock(&data->forks[philo->left_fork_id]);
        return;
    }
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
    precise_sleep(data->time_to_eat);
    pthread_mutex_lock(&data->meal_lock);
    philo->meals_eaten++;
    pthread_mutex_unlock(&data->meal_lock);
}

/**
 * put_down_forks - handle philosopher putting down forks
 * 
 * @philo: Pointer to philosopher data
 */
void put_down_forks(t_philo *philo)
{
    t_data *data;
    
    data = philo->data;
    pthread_mutex_unlock(&data->forks[philo->left_fork_id]);
    pthread_mutex_unlock(&data->forks[philo->right_fork_id]);
}