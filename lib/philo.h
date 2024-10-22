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
# include <unistd.h>
# include <stdbool.h>
# include <limits.h>
# include <pthread.h>
# include <sys/time.h>
# include <stdio.h>
# include <errno.h>
# include <string.h>
// Reset color
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
# define STR_USAGE "usage: <number_philo> <time_die> <time_eat> <time_sleep>"
# define STR_ERR_INPUT_DIGIT	"Not a unsigned int between 0 and 2147483647."
# define STR_ERR_OVER_INT_MAX	"One parameter is too big INT_MAX is the limit."
# define STR_INVALID_INPUT_EXIT	"Error: Invalid input. Program will end safely."
# define STR_ERR_THREAD	"%s error: Could not create thread."
# define STR_ERR_MALLOC	"%s error: Could not allocate memory."
# define STR_ERR_MUTEX	"%s error: Could not create mutex."
# define ONE_SECOND_IN_MS 1000
# define DEBUG_MODE 0
# define EVEN 0
# define ODD 1
# define OVER_INT_MAX -1
# define TOO_MANY_PHILOS "Please use a number of philosophers <= 200."
# define DELAY_TO_PREVENT_BUST 10

typedef enum e_status
{
	EATING,
	SLEEPING,
	THINKING,
	TAKE_FIRST_FORK,
	TAKE_SECOND_FORK,
	DIED,
}	t_philo_status;

typedef enum e_opcode
{
	LOCK,
	UNLOCK,
	INIT,
	DESTROY,
	CREATE,
	JOIN,
	DETACH,
}	t_opcode;

typedef enum e_time_code
{
	SECOND,
	MILLISECOND,
	MICROSECOND,
}	t_time_code;

typedef struct s_fork
{
	int				fork_id;
	pthread_mutex_t	fork_mutex;
}	t_fork;

typedef struct s_table	t_table;

typedef struct s_philo
{
	int				id;
	long			times_ate;
	bool			alive;
	time_t			last_meal_time_ms;
	t_fork			*first_fork;
	t_fork			*second_fork;
	pthread_t		thread_id;
	pthread_mutex_t	philo_mutex;
	t_table			*table;
}	t_philo;

struct s_table
{
	size_t			philo_nbr;
	time_t			time_to_die_in_ms;
	time_t			time_to_eat_in_ms;
	time_t			time_to_sleep_in_ms;
	long			max_meal_count;
	time_t			start_time_in_ms;
	bool			all_threads_ready;
	bool			end_simulation;
	pthread_t		monitor;
	pthread_mutex_t	write_status_mutex;
	pthread_mutex_t	table_mutex;
	t_fork			*forks;
	t_philo			*philos;
};

//data_init.c
bool	data_init(t_table *table);
// dinner.c
void	*lone_philo(void *data);
void	*dinner_simulation(void *data);
//getter_setter.c
bool	get_bool(pthread_mutex_t *mutex, bool *value);
void	set_bool(pthread_mutex_t *mutex, bool *dest, bool value);
time_t	get_time_t(pthread_mutex_t *mutex, time_t *value);
void	set_time_t(pthread_mutex_t *mutex, time_t *dest, time_t value);
long	get_long(pthread_mutex_t *mutex, long *value);
//monitoring.c
bool	simulation_finished(t_table *table);
void	*dinner_monitor(void *data);
//monitoring_utils.c
bool	are_all_philosophers_alive(t_table *table);
//parsing.c
bool	parse_and_validate_table_args(t_table *table,
			int argc, char *argv[]);
//parsing_utils.c
bool	is_valid_input(const char *str);
long	ft_atol(const char *str);
//safe_function_handler
void	*safe_malloc(size_t bytes);
bool	safe_mutex_handle(pthread_mutex_t *mutex, t_opcode opcode,
			const char *mutex_name);
bool	safe_thread_handle(pthread_t *thread, void *(*foo)(void*),
			void *data, t_opcode opcode);
//time.c
time_t	gettime(t_time_code time_code);
void	wait_until_all_threads_ready(t_table *table);
void	sim_start_delay(time_t start_time);
void	precise_usleep(time_t sleep_time, t_table *table);
//utils.c
int		error_msg(const char *str, int exit_nbr);
int		error_max_int_msg(const long exceeded_value, const int exit_nbr);
int		error_failure(const char *str, t_table *table);
void	cleanup_simulation(t_table *table);
//write_status.c
void	write_status(t_philo_status status, t_philo *philo, bool debug);
#endif //PHILO_H
