#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include <sys/time.h>
# include <limits.h>
# include <pthread.h>
# include <string.h>

typedef struct s_philo
{
    int             id;
    int             left_fork_id;
    int             right_fork_id;
    int             meals_eaten;        /* number of meals eaten */
    long long       last_meal_time;     /* timestamp of last meal */
    struct s_data   *data;              /* pointer to shared data */
    pthread_t       thread_id;          /* thread id for this philosopher */
}   t_philo;

/* structure to hold simulation data and settings*/
typedef struct s_data
{
    int             num_philos;
    int             time_to_die;
    int             time_to_eat;
    int             time_to_sleep;
    int             num_meals;          /* optional: number of meals to eat */
    int             meals_specified;    /* flag: was num_meals specified(1)? */
    int             simulation_end;     /* flag for ending simulation */
    long long       start_time;         /* start time of simulation */
    pthread_mutex_t *forks;             /* array of mutex locks for forks */
    pthread_mutex_t write_lock;         /* mutex for writing the console */
    pthread_mutex_t meal_lock;          /* mutex for meal-related operations */
    pthread_mutex_t end_lock;           /* mutex for ending simulation */
    t_philo         *philosophers;      /* array of philosophers*/
}   t_data;

/* utils */
int ft_atoi(char *str);
int check_args(int ac, char **av);

/* init */
int init_data(t_data *data, int ac, char **av);

/* time */
long long get_time();
long long	time_diff(long long past, long long present);
void precise_sleep(long long time_sleep_in_ms);

/* simulation */
int start_simulation(t_data *data);
#endif