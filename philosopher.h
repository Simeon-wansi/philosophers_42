/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sngantch <sngantch@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/17 13:32:10 by sngantch          #+#    #+#             */
/*   Updated: 2025/03/24 21:04:35 by sngantch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHER_H
# define PHILOSOPHER_H

# include <stdio.h> //printf
# include <stdlib.h> //exit , malloc , free
# include <unistd.h> //usleep, sleep
# include <sys/time.h>	//gettimeofday
# include <limits.h> //INT_MAX
# include <stdbool.h>
# include <pthread.h> //pthread_create pthread_join pthread_mutex pthread_mutex_init
# include <errno.h>
typedef struct s_philo t_philo;
typedef struct s_table t_table;
typedef pthread_mutex_t t_mutex;


/* Philo states*/
typedef enum e_status
{
	EATING,
	SLEEPING,
	THINKING,
	TAKE_RIGHT_FORK,
	TAKE_LEFT_FORK,
	DIED
}      t_philo_status;
/* Opcode for mutex | thread functions*/

typedef enum e_opcode
{
	LOCK,
	UNLOCK,
	INIT,
	DESTROY,
	CREATE,
	JOIN,
	DETACH
}    t_opcode;

typedef struct s_fork
{
	t_mutex fork;
	int fork_id;
}  t_fork;


/* code for gettime*/
typedef enum e_time_code
{
	SECOND,
	MILISECOND,
	MICROSECOND
}	t_time_code;

typedef struct s_program
{
	int				dead_flag;
	pthread_mutex_t	*write_lock;
	pthread_mutex_t	*dead_lock;
	pthread_mutex_t	*meal_lock;
	t_philo			*philos;
}					t_program;
/* At the compilation, we must have 4 to 5 argument
./philo number_of_philosophers time_to_die time_to_eat time_to_sleep [number_of_times_each_philosopher_must_eat] */
typedef struct s_philo
{
	int 				id;
	long  				meal_counter;
	bool 				full;
	long				last_meal_time; // time passed from the last meal
	t_fork	*r_fork;
	t_fork	*l_fork;
	pthread_t		thread_id; // A philo is a thread of the program
	t_mutex			philo_mutex; // usefull for the races with the monitor 
	t_table 		*table;
}					t_philo;


/* table container of all the general data of the program*/

typedef struct s_table
{
	long philo_nbr;
	long time_to_die;
	long time_to_eat;
	long time_to_sleep;
	long nbr_limit_meal;
	long start_simulation;
	bool end_simlation; // a philo died or all philo are full
	bool all_threads_ready; // for synchronization philos
	t_mutex table_mutex; // avoid races while reading frm table
	t_mutex write_mutex;
	t_fork *forks;
	t_philo *philos;
}  t_table;

/*Utils func*/
long gettime(t_time_code time_code);
void precise_usleep(long usec, t_table *table);
void error_exit(const char *str);

void parse_input(t_table *table, char **av);
void *save_malloc(size_t bytes);
static void handle_mutex_error(int status, t_opcode opcode);
void safe_mutex_handle(t_mutex *mutex, t_opcode opcode);
static void handle_thread_error(int status, t_opcode opcode);
void safe_thread_handle(pthread_t *thread, void*(*foo)(void *), void *data, t_opcode opcode);
void	data_init( t_table *table);


/* Synchro utils*/
void wait_all_threads(t_table *table);


/*gettime*/
long gettime(t_time_code time_code);

/* setters and getters*/
void set_bool(t_mutex *mutex, bool *dest, bool value);
bool get_bool(t_mutex *mutex, bool *value);
void set_long(t_mutex *mutex, long *dest, long value);
bool simulation_finished(t_table *table);


/*write*/
void write_status(t_philo_status status, t_philo *philo, bool debug);

// start dnner 
void dinner_start(t_table *table);
#endif