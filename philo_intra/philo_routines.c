#include "includes/philo.h"

void *philosopher_routine(void *arg)
{
    t_philo *philo;

    philo = (t_philo *)arg;
    if (philo->data->num_philos > 1 && philo->id % 2 == 0)
    {
        print_status(philo->data, philo->id, THINKING);
        precise_sleep(philo->data->time_to_eat / 2);
    }
    while (!simulation_finished(philo->data))
    {
        if (take_forks(philo) == 0)
        {
            eat(philo);
            put_down_forks(philo);
            if (simulation_finished(philo->data))
                break ;
            print_status(philo->data, philo->id, SLEEPING);
            precise_sleep(philo->data->time_to_sleep);
            if (simulation_finished(philo->data))
                break ;
            print_status(philo->data, philo->id, THINKING);
            if (philo->data->num_philos % 2 == 1)
            {
                long long think_time = philo->data->time_to_eat * 2 - philo->data->time_to_sleep;
                if (think_time > 0 && think_time < 100)
                    precise_sleep(think_time);
                else
                    precise_sleep(1);
            }

        }
        else
        {
            // If couldn't get forks, small delay before retrying
            usleep(100);
        }
    }
    return (NULL);
}

// void    last_one(t_philo *philo, t_data *data)
// {
//     pthread_mutex_lock(&data->forks[philo->right_fork_id]);
//     print_status(data, philo->id, TAKEN_FORK);
//     pthread_mutex_lock(&data->forks[philo->left_fork_id]);
//     print_status(data, philo->id, TAKEN_FORK);
// }

// void take_forks(t_philo *philo)
// {
//     t_data  *data;

//     data = philo->data;
//     if (data->num_philos == 1)
//     {
//         pthread_mutex_lock(&data->forks[philo->left_fork_id]);
//         print_status(data, philo->id, TAKEN_FORK);
//         // Wait for death - single philosopher cannot eat
//         while (!simulation_finished(data))
//             usleep(1000);
//         pthread_mutex_unlock(&data->forks[philo->left_fork_id]);
//         return (1);
//     }
//     if (philo->left_fork_id < philo->right_fork_id)
//     {
//         pthread_mutex_lock(&data->forks[philo->left_fork_id]);
//         print_status(data, philo->id, TAKEN_FORK);
//         pthread_mutex_lock(&data->forks[philo->right_fork_id]);
//         print_status(data, philo->id, TAKEN_FORK);
//     }
//     else
//         last_one(philo, data);
// }

void eat(t_philo *philo)
{
    t_data *data;
    
    data = philo->data;
    pthread_mutex_lock(&data->meal_lock);
    philo->is_eating = 1;
    philo->last_meal_time = get_time();
    pthread_mutex_unlock(&data->meal_lock);
    print_status(data, philo->id, EATING);
    precise_sleep(data->time_to_eat);
    pthread_mutex_lock(&data->meal_lock);
    philo->meals_eaten++;
    philo->is_eating = 0;
    pthread_mutex_unlock(&data->meal_lock);
}

void put_down_forks(t_philo *philo)
{
    t_data *data;
    
    data = philo->data;
    // Always release in the same order as acquired to prevent issues
    if (philo->left_fork_id < philo->right_fork_id)
    {
        pthread_mutex_unlock(&data->forks[philo->left_fork_id]);
        pthread_mutex_unlock(&data->forks[philo->right_fork_id]);
    }
    else
    {
        pthread_mutex_unlock(&data->forks[philo->right_fork_id]);
        pthread_mutex_unlock(&data->forks[philo->left_fork_id]);
    }
}