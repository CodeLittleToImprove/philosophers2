/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitoring_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbui-quo <tbui-quo@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/18 16:15:06 by tbui-quo          #+#    #+#             */
/*   Updated: 2024/10/18 16:17:17 by tbui-quo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../lib/philo.h"

static void	mark_philosopher_dead(t_philo *philo)
{
	philo->alive = false;
	set_bool(&philo->table->table_mutex, &philo->table->end_simulation, true);
	write_status(DIED, philo, DEBUG_MODE);
}

static bool	has_starved(t_philo *philo)
{
	time_t	current_time_ms;
	time_t	elapsed_time_since_last_meal;

	current_time_ms = gettime(MILLISECOND);
	elapsed_time_since_last_meal = current_time_ms - philo->last_meal_time_ms;
	if (elapsed_time_since_last_meal >= philo->table->time_to_die_in_ms)
	{
		mark_philosopher_dead(philo);
		return (true);
	}
	return (false);
}

static bool	is_philo_dead(t_philo *philo)
{
	bool	has_died;

	has_died = false;
	pthread_mutex_lock(&philo->philo_mutex);
	if (has_starved(philo) == true)
		has_died = true;
	pthread_mutex_unlock(&philo->philo_mutex);
	return (has_died);
}

static bool	has_philo_ate_enough(t_philo *philo, long max_meal_count)
{
	if (max_meal_count == -1)
		return (false);
	if (get_long(&philo->philo_mutex, &philo->times_ate) >= max_meal_count)
		return (true);
	return (false);
}

bool	are_all_philosophers_alive(t_table *table)
{
	bool	all_ate_enough;
	size_t	i;

	all_ate_enough = true;
	i = 0;
	while (i < table->philo_nbr)
	{
		if (is_philo_dead(&table->philos[i]) == true)
			return (false);
		if (!has_philo_ate_enough(&table->philos[i], table->max_meal_count))
			all_ate_enough = false;
		i++;
	}
	if (table->max_meal_count != -1 && all_ate_enough)
		set_bool(&table->table_mutex, &table->end_simulation, true);
	return (true);
}
