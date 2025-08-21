#include "philo.h"

void *philosopher_routine(void *arg)
{
    t_philo *philo;
    long long think_time;

    philo = (t_philo *)arg;
    if (philo->id % 2 == 0)
    {
        print_status(philo->data, philo->id, THINKING);
        usleep(1000);
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
            // precise_sleep(philo->data->time_to_sleep);
            usleep(philo->data->time_to_sleep * 1000);
            if (simulation_finished(philo->data))
                break ;
            print_status(philo->data, philo->id, THINKING);
            if (philo->data->num_philos % 2 == 1 && philo->id % 2 == 1)
            {
                if (philo->data->time_to_eat >= philo->data->time_to_sleep)
                {
                    think_time = philo->data->time_to_eat - philo->data->time_to_sleep;
                    // precise_sleep(think_time);
                    usleep((think_time * 1000));
                }
                // else
                //     usleep(3000);
            }
        }
        else
        {
            usleep(100);
        }
    }
    return (NULL);
}

void eat(t_philo *philo)
{
    t_data *data;
    
    data = philo->data;
    // Update last meal time BEFORE eating starts
    pthread_mutex_lock(&data->meal_lock);
    philo->last_meal_time = get_time();
    pthread_mutex_unlock(&data->meal_lock);
    print_status(data, philo->id, EATING);
    usleep(data->time_to_eat * 1000);
    pthread_mutex_lock(&data->meal_lock);
    philo->meals_eaten++;
    pthread_mutex_unlock(&data->meal_lock);
}

void put_down_forks(t_philo *philo)
{
    t_data *data;
    
    data = philo->data;
    // Always release in the same order as acquired to prevent issues
    if (philo->left_fork_id < philo->right_fork_id)
    {
        pthread_mutex_unlock(&data->forks[philo->right_fork_id]);
        pthread_mutex_unlock(&data->forks[philo->left_fork_id]);
    }
    else
    {
        pthread_mutex_unlock(&data->forks[philo->left_fork_id]);
        pthread_mutex_unlock(&data->forks[philo->right_fork_id]);
    }
}
        
