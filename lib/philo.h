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
#define PHILO_H

# include <stdlib.h>
# include <stdbool.h>
# include <limits.h>
# include <pthread.h>
# include <sys/time.h>
# include <stdio.h>
# include <errno.h>

// Reset
#define RESET "\033[0m"

// Bold text colors
#define BLA "\033[1;30m"  // Black
#define R "\033[1;31m"  // Red
#define G "\033[1;32m"  // Green
#define Y "\033[1;33m"  // Yellow
#define B "\033[1;34m"  // Blue
#define M "\033[1;35m"  // Magenta
#define C "\033[1;36m"  // Cyan
#define W "\033[1;37m"  // White

#define DEBUG_MODE 1
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

typedef enum
{
	ERROR_CRITICAL,
	ERROR_MINOR
} ErrorLevel;

typedef struct s_fork
{
	int				fork_id;
	pthread_mutex_t	fork_mutex;
}	t_fork;

typedef struct s_table	t_table;

typedef struct s_philo
{
	int			id;
	long		meals_counter;
	t_fork		*first_fork;
	t_fork		*second_fork;
	pthread_t	thread_id;
	pthread_mutex_t	philo_mutex;
	t_table		*table;
}	t_philo;

struct s_table
{
	size_t			philo_nbr;
	long			time_to_die_in_ms;
	long			time_to_eat_in_ms;
	long			time_to_sleep_in_ms;
	long			nbr_limit_meals;
	pthread_t	monitor;
	pthread_mutex_t	write_mutex;
	t_fork			*forks;
	t_philo			*philos;
};

//parsing.c
bool	parse_input(t_table *table, const int argc, char *argv[]);
//safe_function_handler
void			*safe_malloc(size_t bytes);
void			safe_mutex_handle(pthread_mutex_t *mutex, t_opcode opcode);
void			safe_thread_handle(pthread_t *thread, void *(foo)(void*),
						void *data, t_opcode opcode);

//getter_setter.c
void	set_bool(pthread_mutex_t *mutex, bool *dest, bool value);
bool	get_bool(pthread_mutex_t *mutex, bool *value);
void	set_long(pthread_mutex_t *mutex, long *dest, long value);
long	get_long(pthread_mutex_t *mutex, long *value);
// utils.c
int	error_exit(const char *error, ErrorLevel error_level);
// write_status.c
void	write_status(t_philo_status status, t_philo *philo, bool debug);
#endif //PHILO_H
