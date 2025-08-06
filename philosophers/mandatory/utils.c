#include "includes/philo.h"

int ft_atoi(char *str)
{
    long    result;
    int         sign;
    int         i;

    result = 0;
    sign = 1;
    i = 0;
    while (str[i] == ' ' || (str[i] >= 9 && str[i] <= 13))
        i++;
    if (str[i] == '-' || str[i] == '+')
    {
        if (str[i] == '-')  
            sign = -1;
        i++;
    }
    while (str[i] >= '0' && str[i] <= '9')
    {
        result = result * 10 + (str[i] - 48);
        if (result * sign > INT_MAX || result * sign < INT_MIN)
            return (-1);
        i++;
    }
    // if (str[i] != '\0')
    //     return (-1);
    return (result * sign);
}

int is_digit(int nbr)
{
    return (nbr >= '0' && nbr <= '9');
}

/**
 * Validate command-line arguments
 * 
 * @param ac Number of command-line arguments
 * @param av Array of command-line arguments
 * @return 0 on success, 1 on error
 */
int check_args(int ac, char **av)
{
    int i;
    int j;

    i = 1;
    while (i < ac)
    {
        j = 0;
        while (av[i][j])
        {
            if (!is_digit(av[i][j]))
            {
                printf("Error: Arguments must be positive integers\n");
                return (1);
            }
            j++;
        }
        i++;
    }
    return (0);
}

/**
 * Print philosopher status with timestamp
 * 
 * @data: Pointer to data structure
 * @id: Philosopher ID
 * @status: Status message to print
 */

void    print_status(t_data *data, int id, char *status)
{
    long long current_time;

    pthread_mutex_lock(&data->write_lock);
    if (!simulation_finished(data))
    {
        current_time = get_time();
        if (current_time != -1)
        {
            printf("%lld %d %s\n",
                time_diff(data->start_time, current_time), id, status);
        }
    }
    pthread_mutex_unlock(&data->write_lock);
}

/**
 * Print error message and clean up resources
 * 
 * @msg: Error message to print
 * @data: Pointer to data structure
 * Return: 1 (error code)
 */

int error_exit(char *message, t_data *data)
{
    printf("Error : %s\n", message);
    cleanup(data);
    return (1);
}