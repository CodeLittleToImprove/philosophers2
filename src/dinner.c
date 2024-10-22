/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dinner.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbui-quo <tbui-quo@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/22 18:15:35 by tbui-quo          #+#    #+#             */
/*   Updated: 2024/08/22 18:15:35 by tbui-quo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../lib/philo.h"

static	void	eat_routine(t_philo *philo)
{
	if (get_bool(&philo->philo_mutex, &philo->alive) == false)
		return;
	safe_mutex_handle(&philo->first_fork->fork_mutex, LOCK, "first fork lock");
	write_status(TAKE_FIRST_FORK, philo, DEBUG_MODE);
	safe_mutex_handle(&philo->second_fork->fork_mutex, LOCK, "second fork lock");
	write_status(TAKE_SECOND_FORK, philo, DEBUG_MODE);
	safe_mutex_handle(&philo->philo_mutex, LOCK, "philo lock");
	philo->last_meal_time_ms = gettime(MILLISECOND);
	safe_mutex_handle(&philo->philo_mutex, UNLOCK, "philo unlock");
	write_status(EATING, philo, DEBUG_MODE);
	precise_usleep(philo->table->time_to_eat_in_ms, philo->table);
	if (!simulation_finished(philo->table))
	{
		safe_mutex_handle(&philo->philo_mutex, LOCK, "philo times ate lock");
		philo->times_ate += 1;
		safe_mutex_handle(&philo->philo_mutex, UNLOCK, "philo times ate unlock");
	}
	safe_mutex_handle(&philo->first_fork->fork_mutex, UNLOCK, "first fork unlock");
	safe_mutex_handle(&philo->second_fork->fork_mutex, UNLOCK, "second fork unlock");
}

static void	think_routine(t_philo *philo, bool silent)
{
	time_t	time_to_think_in_ms;

	pthread_mutex_lock(&philo->philo_mutex);
	time_to_think_in_ms = (philo->table->time_to_die_in_ms
			- (gettime(MILLISECOND) - philo->last_meal_time_ms)
			- philo->table->time_to_eat_in_ms) / 2;
	pthread_mutex_unlock(&philo->philo_mutex);
	if (silent == false)
		write_status(THINKING, philo, DEBUG_MODE);
	if (time_to_think_in_ms < 0)
		time_to_think_in_ms = 0;
	if (time_to_think_in_ms == 0 && silent == true)
		time_to_think_in_ms = 1;
	if (time_to_think_in_ms > 600)
		time_to_think_in_ms = 200;
	precise_usleep(time_to_think_in_ms, philo->table);
}

void	*lone_philo(void *data)
{
	t_philo	*philo;

	philo = (t_philo *)data;
	wait_until_all_threads_ready(philo->table);
	pthread_mutex_lock(&philo->philo_mutex);
	philo->last_meal_time_ms = philo->table->start_time_in_ms;
	pthread_mutex_unlock(&philo->philo_mutex);
	write_status(TAKE_FIRST_FORK, philo, DEBUG_MODE);
	while (!simulation_finished(philo->table))
		usleep(200);
	return (NULL);
}

void	*dinner_simulation(void *data)
{
	t_philo	*philo;

	philo = (t_philo *)data;
	wait_until_all_threads_ready(philo->table);
	set_time_t(&philo->philo_mutex, &philo->last_meal_time_ms,
		philo->table->start_time_in_ms);
	if (philo->id % 2 == ODD)
		think_routine(philo, true);
	while (!simulation_finished(philo->table))
	{
		eat_routine(philo);
		write_status(SLEEPING, philo, DEBUG_MODE);
		precise_usleep(philo->table->time_to_sleep_in_ms, philo->table);
		think_routine(philo, false);
	}
	return (NULL);
}