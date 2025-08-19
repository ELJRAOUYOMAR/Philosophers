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
    return (result * sign);
}

int is_digit(int nbr)
{
    return (nbr >= '0' && nbr <= '9');
}

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

void    print_status(t_data *data, int id, char *status)
{
    long long current_time;

    pthread_mutex_lock(&data->write_lock);
    if (!simulation_finished(data))
    {
        current_time = get_time();
        if (current_time != 1)
        {
            printf("%lld %d %s\n",
                time_diff(data->start_time, current_time), id, status);
        }
    }
    pthread_mutex_unlock(&data->write_lock);
}

int error_exit(char *message, t_data *data)
{
    printf("Error : %s\n", message);
    clean_up(data);
    return (1);
}