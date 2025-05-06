# include "includes/philo.h"

int main(int ac, char **av)
{
    t_data data;
    memset(&data, 0, sizeof(t_data));
    if (ac < 5 || ac > 6)
    {
        printf("Invalid number of arguments⚠️\n");
        printf("Usage: [%s] [number_of_philos] [time_to_die] [time_to_eat] "
                "[time_to_sleep] [number_of_times_each_philosopher_must_eat]\n", av[0]);
        printf("the last parameter is optionalℹ️\n");
        return (1);
    }
    if (check_args(ac, av))
		return (1);
	if (init_data(&data, ac, av))
		return (1);
	if (init_mutexes(&data))
		return (error_exit(ERR_MUTEX, &data));
	if (init_philosophers(&data))
		return (error_exit(ERR_MALLOC, &data));
	if (start_simulation(&data))
		return (error_exit(ERR_THREAD, &data));
	join_threads(&data);
	cleanup(&data);
	return (0);
}