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

// look how the other repo did it
// add this to philosophers creating

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
	precise_usleep(time_to_think_in_ms, philo->table); // could change everything to usec
}

void	*dinner_simulation(void *data)
{
	t_philo *philo;

	philo = (t_philo *)data;

	wait_until_all_threads_ready(philo->table);
	// maybe use getter setter but with time_t as datatype?
	pthread_mutex_lock(&philo->philo_mutex);
	philo->last_meal_time_ms = philo->table->start_time_in_ms;
	pthread_mutex_unlock(&philo->philo_mutex);
	if (philo->id % 2 == ODD) // is that enough or i need something like de_synchronize_philos
		think_routine(philo, true);
	while (!simulation_finished(philo->table))
	{
		// maybe add boolean if philo is full
		eat_routine(philo);
		write_status(SLEEPING, philo, DEBUG_MODE);
		// precise_usleep(philo->table->time_to_sleep_in_usec, philo->table); // not sure if should just ms or usec
		think_routine(philo, false);
	}
	return (NULL);
}