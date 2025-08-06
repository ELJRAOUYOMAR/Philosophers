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

/* Error codes */
# define ERR_ARGS        "Invalid arguments\n"
# define ERR_MALLOC      "Memory allocation failed\n"
# define ERR_MUTEX       "Mutex initialization failed\n"
# define ERR_THREAD      "Thread creation failed\n"

/* Status messages */
# define TAKEN_FORK      "has taken a fork"
# define EATING          "is eating"
# define SLEEPING        "is sleeping"
# define THINKING        "is thinking"
# define DIED            "died"

typedef struct s_philo
{
    int             id;
    pthread_t       thread_id;          /* thread id for this philosopher */
    int             left_fork_id;
    int             right_fork_id;
    int             meals_eaten;        /* number of meals eaten */
    long long       last_meal_time;     /* timestamp of last meal */
    struct s_data   *data;              /* pointer to shared data */
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
    pthread_t       monitor_thread;     /* monitor thread ID */
    pthread_mutex_t *forks;             /* array of mutex locks for forks */
    pthread_mutex_t write_lock;         /* mutex for writing the console */
    pthread_mutex_t meal_lock;          /* mutex for meal-related operations */
    pthread_mutex_t end_lock;           /* mutex for ending simulation */
    t_philo         *philosophers;      /* array of philosophers*/
}   t_data;

/* utils */
int ft_atoi(char *str);
int check_args(int ac, char **av);
void    print_status(t_data *data, int id, char *status);
int error_exit(char *message, t_data *data);

/* init */
int init_data(t_data *data, int ac, char **av);
int init_mutexes(t_data *data);
int init_philosophers(t_data *data);

/* time */
long long get_time();
long long	time_diff(long long past, long long present);
void precise_sleep(long long time_sleep_in_ms);

/* routines */
void *philosopher_routine(void *arg);
int take_forks(t_philo *philo);
void eat(t_philo *philo);
void put_down_forks(t_philo *philo);

/* monitoring */
void *monitor_routine(void *arg);
int	check_death(t_data *data, int *i);
int check_each_philo_eat(t_data *data);

/* simulation */
int start_simulation(t_data *data);
int simulation_finished(t_data *data);

/* cleanup */
void *cleanup(t_data *data);
void join_threads(t_data *data);

#endif