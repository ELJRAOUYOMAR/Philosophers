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
    if (philo->data->num_philos == 1)
    {
        pthread_mutex_lock(&philo->data->forks[philo->left_fork_id]);
        print_status(philo->data, philo->id, TAKEN_FORK);
        // Single philosopher can't eat (needs 2 forks), so just wait to die
        while (!simulation_finished(philo->data))
            usleep(1000);
        pthread_mutex_unlock(&philo->data->forks[philo->left_fork_id]);
        return (NULL);
    }
    // multi philos logic
    // if odd numbered philosopher, delay start to prevent deadlock
    if (philo->id % 2 == 1)
    {
        print_status(philo->data, philo->id, THINKING);
        precise_sleep(philo->data->time_to_eat);
    }
    while (!simulation_finished(philo->data))
    {
        if (take_forks(philo))
            break; // Failed to take forks or simulation ended
        eat(philo);
        put_down_forks(philo);
        if (simulation_finished(philo->data))
            break;
        print_status(philo->data, philo->id, SLEEPING);
        precise_sleep(philo->data->time_to_sleep);
        if (simulation_finished(philo->data))
            break;
        print_status(philo->data, philo->id, THINKING);
        if (philo->data->num_philos % 2)
        {
            if (philo->id % 2)
            {
                if (philo->data->time_to_eat >= philo->data->time_to_sleep)
                    usleep((philo->data->time_to_eat - philo->data->time_to_sleep + 10) * 1000);
            }
        }
    }
    return (NULL);
}

/**
 * Handle philosopher taking forks
 * 
 * @philo: Pointer to philosopher data
 */
int take_forks(t_philo *philo)
{
    t_data  *data;

    data = philo->data;
    if (simulation_finished(data))
        return (1);
    if (philo->left_fork_id < philo->right_fork_id)
    {
        pthread_mutex_lock(&data->forks[philo->left_fork_id]);
        if (simulation_finished(data))
        {
            pthread_mutex_unlock(&data->forks[philo->left_fork_id]);
            return (1);
        }
        print_status(data, philo->id, TAKEN_FORK);
        pthread_mutex_lock(&data->forks[philo->right_fork_id]);
        if (simulation_finished(data))
        {
            pthread_mutex_unlock(&data->forks[philo->right_fork_id]);
            pthread_mutex_unlock(&data->forks[philo->left_fork_id]);
            return (1);
        }
        print_status(data, philo->id, TAKEN_FORK);
    }
    else
    {
        pthread_mutex_lock(&data->forks[philo->right_fork_id]);
        if (simulation_finished(data))
        {
            pthread_mutex_unlock(&data->forks[philo->right_fork_id]);
            return (1);
        }
        print_status(data, philo->id, TAKEN_FORK);
        pthread_mutex_lock(&data->forks[philo->left_fork_id]);
        if (simulation_finished(data))
        {
            pthread_mutex_unlock(&data->forks[philo->left_fork_id]);
            pthread_mutex_unlock(&data->forks[philo->right_fork_id]);
            return (1);
        }
        print_status(data, philo->id, TAKEN_FORK);
    }
    return (0); // success: taking both forks
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