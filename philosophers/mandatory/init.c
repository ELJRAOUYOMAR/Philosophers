#include "includes/philo.h"

/**
 * Initialize simulation data from command-line arguments
 * 
 * @data: Pointer to data structure
 * @argc: Number of command-line arguments
 * @argv: Array of command-line arguments
 * 
 * Return: 0 on success, 1 on error
 */
int init_data(t_data *data, int ac, char **av)
{
    data->num_philos = ft_atoi(av[1]);
    data->time_to_die = ft_atoi(av[2]);
    data->time_to_eat = ft_atoi(av[3]);
    data->time_to_sleep = ft_atoi(av[4]);
    data->simulation_end = 0;
    data->monitor_thread = 0;
    if (ac == 6)
    {
        data->num_meals = ft_atoi(av[5]);
        data->meals_specified = 1;
    }
    else
    {
        data->meals_specified = 0;
        data->num_meals = -1;
    }
    if (data->num_philos <= 0 || data->time_to_die <= 0 
        || data->time_to_eat <= 0 || data->time_to_sleep <= 0
        || (data->meals_specified == 1 && data->num_meals <= 0))
    {
        printf("Error: Arguments must be positive integers⚠️\n");
        return (1);
    }
    // printf("%d %d %d %d %d", data->num_philos, data->time_to_die, data->time_to_eat, data->time_to_sleep
    //     , data->num_meals);
    return (0);
}

/**
 * Initialize mutexes for forks and other shared resources
 * 
 * @param data Pointer to data structure
 * @return 0 on success, 1 on error
 */
int init_mutexes(t_data *data)
{
    int i;

    data->forks = malloc(sizeof(pthread_mutex_t) * data->num_philos);
    if (!data || !data->forks)
    {
        printf(ERR_MALLOC);
        return (1);
    }
    i = 0;
    while (i < data->num_philos)
    {
        if (pthread_mutex_init(&data->forks[i], NULL) != 0)
            return (1);
        i++;
    }
    if (pthread_mutex_init(&data->write_lock, NULL) != 0)
            return (1);
    if (pthread_mutex_init(&data->meal_lock, NULL) != 0)
        return (1);
    if (pthread_mutex_init(&data->end_lock, NULL) != 0)
        return (1);
    return (0);
}

/**
 * Initialize philosopher data structures
 * 
 * @data: Pointer to data structure
 *
 * Return: 0 on success, 1 on error
 */
int init_philosophers(t_data *data)
{
    int i;

    data->philosophers = malloc(sizeof(t_philo) * data->num_philos);
    if (!data || !data->philosophers)
        return (1);
    i = 0;
    while (i < data->num_philos)
    {
        data->philosophers[i].id = i + 1;
        data->philosophers[i].left_fork_id = i;
        // if (i == data->num_philos - 1)
        //     data->philosophers[i].right_fork_id = 0;
        // else 
        //     data->philosophers[i].right_fork_id = i + 1;    // last philo's right fork is the first one
        data->philosophers[i].right_fork_id = (i + 1) % data->num_philos;
        data->philosophers[i].meals_eaten = 0;
        data->philosophers[i].last_meal_time = 0;
        data->philosophers[i].data = data;
        i++;
    }
    return (0);
}