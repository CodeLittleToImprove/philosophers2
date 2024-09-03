/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitoring.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbui-quo <tbui-quo@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/27 18:45:35 by tbui-quo          #+#    #+#             */
/*   Updated: 2024/08/27 18:45:35 by tbui-quo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../lib/philo.h"

bool	simulation_finished(t_table *table)
{
	bool	simulation_ended;

	simulation_ended = false;
	pthread_mutex_lock(&table->table_mutex);
	if (table->end_simulation == true)
		simulation_ended = true;
	pthread_mutex_unlock(&table->table_mutex);
	return (simulation_ended);
}

static bool	has_starved(t_philo *philo)
{
	time_t	current_time_ms;
	time_t	elapsed_time_since_last_meal;

	current_time_ms = gettime(MILLISECOND);
	elapsed_time_since_last_meal = current_time_ms - philo->last_meal_time_ms;
	if (elapsed_time_since_last_meal >= philo->table->time_to_die_in_ms)
	{
		set_bool(&philo->table->table_mutex, &philo->table->end_simulation, true);
		write_status(DIED, philo, DEBUG_MODE);
		return (true);
	}
	return (false);
}

static bool	is_philo_dead(t_philo *philo)
{
	bool has_died;

	has_died = false;
	pthread_mutex_lock(&philo->philo_mutex);
	if (has_starved(philo) == true)
		has_died = true;
	pthread_mutex_unlock(&philo->philo_mutex);

	return (has_died);
}

static bool has_philo_ate_enough(t_philo *philo, long max_meal_count)
{
	bool	ate_enough;

	ate_enough = true;
	if (max_meal_count != -1 && philo->times_ate < max_meal_count)
		ate_enough = false;

	return (ate_enough);
}

static bool	are_all_philosophers_alive(t_table *table)
{
	bool	all_ate_enough;
	size_t	i;

	all_ate_enough = true;
	i = 0;
	while (i < table->philo_nbr)
	{
		if(is_philo_dead(&table->philos[i]) == true)
			return (true);
		if(!has_philo_ate_enough(&table->philos[i], table->max_meal_count))
			all_ate_enough = false;
		i++;
	}
	if (table->max_meal_count != -1 && all_ate_enough) // maybe not needed
	{
		set_bool(&table->table_mutex, &table->end_simulation, true);
	}
	return (false);
}
// error somewhere because philo always dead
void	*dinner_monitor(void *data)
{
	t_table	*table;

	table = (t_table *) data;
	if (table->max_meal_count == 0)
		return (NULL);
	set_bool(&table->table_mutex, &table->end_simulation,false);
	while (true)
	{
		if (are_all_philosophers_alive(table) == true)
			return (NULL);
		usleep(1000);
	}
	// int status = pthread_mutex_lock(&table->table_mutex);
	// printf("status after lock: %d\n", status);
	// table->end_simulation = false;
	// status = pthread_mutex_unlock(&table->table_mutex);
	// printf("status after unlock: %d\n", status);
}