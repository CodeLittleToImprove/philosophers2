/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbui-quo <tbui-quo@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/14 17:28:53 by tbui-quo          #+#    #+#             */
/*   Updated: 2024/08/14 17:28:53 by tbui-quo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdlib.h>
#include <unistd.h>
# include <stdbool.h>
# include <limits.h>
# include <pthread.h>
# include <sys/time.h>
# include <stdio.h>
# include <errno.h>

// Reset
# define RESET "\033[0m"

// Bold text colors
# define BLA "\033[1;30m"  // Black
# define R "\033[1;31m"  // Red
# define G "\033[1;32m"  // Green
# define Y "\033[1;33m"  // Yellow
# define B "\033[1;34m"  // Blue
# define M "\033[1;35m"  // Magenta
# define C "\033[1;36m"  // Cyan
# define W "\033[1;37m"  // White

# define STR_ERR_NO_DIGIT	"Input contains not only digits"
# define STR_USAGE	"usage: ./philo <number_of_philosophers> " \
"<time_to_die> <time_to_eat> <time_to_sleep> " \
"[number_of_times_each_philosopher_must_eat]\n"
# define STR_ERR_INPUT_DIGIT	"Not a valid unsigned integer between 0 and 2147483647.\n"
# define STR_ERR_OVER_INT_MAX	"The value is too big, INT_MAX is the limit"
# define STR_INVALID_INPUT_EXIT	"Error: Invalid input detected. The program will now terminate safely."
# define STR_ERR_INPUT_POFLOW	"There must be between 1 and 250 philosophers.\n"
# define STR_ERR_THREAD	"%s error: Could not create thread.\n"
# define STR_ERR_MALLOC	"%s error: Could not allocate memory.\n"
# define STR_ERR_MUTEX	"%s error: Could not create mutex.\n"
# define ONE_SECOND_IN_MS 1000
# define DEBUG_MODE 1
# define EVEN 0
# define ODD 1
typedef enum e_status
{
	EATING,
	SLEEPING,
	THINKING,
	TAKE_FIRST_FORK,
	TAKE_SECOND_FORK,
	DIED,
} t_philo_status;

typedef enum e_opcode
{
	LOCK,
	UNLOCK,
	INIT,
	DESTROY,
	CREATE,
	JOIN,
	DETACH,
} t_opcode;

typedef enum e_time_code
{
	SECOND,
	MILLISECOND,
	MICROSECOND,
} t_time_code;

typedef struct s_fork
{
	int				fork_id;
	pthread_mutex_t	fork_mutex;
}	t_fork;

typedef struct s_table	t_table;

typedef struct s_philo
{
	int				id;
	long			meals_counter;
	time_t			last_meal_time_ms;
	t_fork			*first_fork;
	t_fork			*second_fork;
	pthread_t		thread_id;
	pthread_mutex_t	philo_mutex;
	t_table			*table;
}	t_philo;

//maybe change datatype of long to time_t
struct s_table
{
	size_t			philo_nbr;
	time_t			time_to_die_in_ms;
	time_t			time_to_eat_in_ms;
	time_t			time_to_sleep_in_ms;
	long			nbr_limit_meals;
	time_t			start_time_in_ms;
	bool			all_threads_ready;
	bool			end_simulation;
	pthread_t		monitor;
	pthread_mutex_t	write_status_mutex;
	pthread_mutex_t	table_mutex;
	t_fork			*forks;
	t_philo			*philos;
};


//parsing.c
bool	parse_and_validate_table_args(t_table *table, const int argc, char *argv[]);
// //safe_function_handler
void			*safe_malloc(size_t bytes);
bool			safe_mutex_handle(pthread_mutex_t *mutex, t_opcode opcode);
bool			safe_thread_handle(pthread_t *thread, void *(*foo)(void*), void *data, t_opcode opcode);

//data_init.c
bool	data_init(t_table *table);
//getter_setter.c
void	set_bool(pthread_mutex_t *mutex, bool *dest, bool value);
bool	get_bool(pthread_mutex_t *mutex, bool *value);
// void	set_long(pthread_mutex_t *mutex, long *dest, long value);
// long	get_long(pthread_mutex_t *mutex, long *value);
// utils.c
int		error_msg(const char *str, int exit_nbr);
int		error_failure(const char *str, t_table *table);
void	cleanup_simulation(t_table *table);
// time.c
time_t	gettime(t_time_code time_code);
void	wait_until_all_threads_ready(t_table *table);
void	precise_usleep(time_t sleep_time_ms, t_table *table);
// write_status.c
void	write_status(t_philo_status status, t_philo *philo, bool debug);
// dinner.c
void	*dinner_simulation(void *data);
// monitoring.c
void	*dinner_monitor(void *data);
bool	simulation_finished(t_table *table);
#endif //PHILO_H
