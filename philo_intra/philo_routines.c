#include "includes/philo.h"

void *philosopher_routine(void *arg)
{
    t_philo *philo;

    philo = (t_philo *)arg;
    if (philo->id % 2 == 1)
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
            // Small think time to prevent busy waiting
            if (philo->data->num_philos % 2 == 1)
                usleep(1000);  // 1ms for odd number of philosophers

        }
    }
    return (NULL);
}

void    last_one(t_philo *philo, t_data *data)
{
    pthread_mutex_lock(&data->forks[philo->right_fork_id]);
    print_status(data, philo->id, TAKEN_FORK);
    pthread_mutex_lock(&data->forks[philo->left_fork_id]);
    print_status(data, philo->id, TAKEN_FORK);
}

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
    philo->last_meal_time = get_time();
    philo->is_eating = 1;
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
    pthread_mutex_unlock(&data->forks[philo->left_fork_id]);
    pthread_mutex_unlock(&data->forks[philo->right_fork_id]);
}