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

// static bool	has_starved(t_philo *philo)
// {
// 	time_t	current_time_ms;
// 	time_t	elapsed_time_since_last_meal;
//
// 	current_time_ms = gettime(MILLISECOND);
// 	elapsed_time_since_last_meal = current_time_ms - philo->last_meal_time_ms;
// 	if (elapsed_time_since_last_meal >= philo->table->time_to_die_in_ms)
// 	{
// 		set_bool(&philo->table->table_mutex, &philo->table->end_simulation, true);
// 		write_status(DIED, philo, DEBUG_MODE);
// 		return (true);
// 	}
// 	return (false);
// }

static void	mark_philosopher_dead(t_philo *philo)
{
	// printf("Philosopher %d has starved. Marking as dead and stopping simulation.\n", philo->id);
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

	// Debugging prints
	// printf("Philosopher %d - Current time (ms): %ld\n", philo->id, current_time_ms);
	// printf("Philosopher %d - Last meal time (ms): %ld\n", philo->id, philo->last_meal_time_ms);
	// printf("Philosopher %d - Elapsed time since last meal (ms): %ld\n", philo->id, elapsed_time_since_last_meal);
	// printf("Philosopher %d - Time to die (ms): %ld\n", philo->id, philo->table->time_to_die_in_ms);
	// printf("Last meal time: %ld, Time to die: %ld\n", elapsed_time_since_last_meal, philo->table->time_to_die_in_ms);

	if (elapsed_time_since_last_meal >= philo->table->time_to_die_in_ms)
	{
		// printf("Philosopher %d has starved. Setting end_simulation flag to true.\n", philo->id);
		// // philo->alive = false;
		// set_bool(&philo->table->table_mutex, &philo->table->end_simulation, true);
		// write_status(DIED, philo, DEBUG_MODE);
		mark_philosopher_dead(philo);
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

// static bool has_philo_ate_enough(t_philo *philo, long max_meal_count)
// {
// 	bool	ate_enough;
//
// 	ate_enough = true;
// 	// if (max_meal_count != -1 && philo->times_ate < max_meal_count)
// 	// {
// 	// 	ate_enough = false;
// 	// }
// 	if (max_meal_count != -1 && philo->times_ate < max_meal_count)
// 	{
// 		// Debugging prints
// 		// printf("true case\n");
// 		// printf("Philosopher %d - Max meal count: %ld\n", philo->id, max_meal_count);
// 		// printf("Philosopher %d - Times ate: %ld\n", philo->id, philo->times_ate);
// 		// printf("Philosopher %d has not eaten enough meals.\n", philo->id);
// 		ate_enough = false;
// 	}
//
// 	return (ate_enough);
// }

// working
// static bool has_philo_ate_enough(t_philo *philo, long max_meal_count)
// {
// 	if (max_meal_count == -1)
// 		return false; // No meal count limit set
//
// 	if (philo->times_ate >= max_meal_count)
// 	{
// 		// printf("Philosopher %d has eaten enough meals.\n", philo->id);
// 		return true;
// 	}
// 	return false;
// }

// debug version because status eats too much
static bool has_philo_ate_enough(t_philo *philo, long max_meal_count)
{
	// Debugging print to check the philosopher's current meal count and the max allowed meal count
	// printf("Checking if philosopher %d has eaten enough meals.\n", philo->id);
	// printf("Philosopher %d has eaten %ld times. Max meal count is %ld.\n", philo->id, philo->times_ate, max_meal_count);

	if (max_meal_count == -1)
		return (false);
	if (philo->times_ate >= max_meal_count)
	{
		// Debugging print to confirm when the philosopher has eaten enough
		// printf("Philosopher %d has eaten enough meals (%ld times). No more meals required.\n", philo->id, philo->times_ate);
		return (true);
	}

	// If the philosopher hasn't eaten enough yet
	// printf("Philosopher %d has not eaten enough. Continuing...\n", philo->id);
	return (false);
}


static bool	are_all_philosophers_alive(t_table *table)
{
	bool	all_ate_enough;
	size_t	i;

	all_ate_enough = true;
	i = 0;
	// printf("in all philosophers alive \n");
	while (i < table->philo_nbr)
	{

		if (is_philo_dead(&table->philos[i]) == true)
		{
			return (false);
		}


		// Check if a philosopher hasn't eaten enough
		if (!has_philo_ate_enough(&table->philos[i], table->max_meal_count))
			all_ate_enough = false;
		i++;
	}

	// If all have eaten enough, stop the simulation
	if (table->max_meal_count != -1 && all_ate_enough)
	{
		printf("set bool end simulation to true because all ate enough\n");
		set_bool(&table->table_mutex, &table->end_simulation, true);
	}


	return (true);
}

// void	*dinner_monitor(void *data) // old version potencial wrong
// {
// 	t_table	*table;
//
// 	table = (t_table *) data;
// 	if (table->max_meal_count == 0)
// 		return (NULL);
// 	set_bool(&table->table_mutex, &table->end_simulation,false);
// 	// printf("monitor thread running \n");
// 	sim_start_delay(table->start_time_in_ms + 10); // small delay to not immedetialy get busted by monitor
//
// 	while (simulation_finished(table) == false)
// 	{
// 		if (!are_all_philosophers_alive(table))
// 			return (NULL);
// 		usleep(1000);
// 	}
// 	return (NULL);
// 	// int status = pthread_mutex_lock(&table->table_mutex);
// 	// printf("status after lock: %d\n", status);
// 	// table->end_simulation = false;
// 	// status = pthread_mutex_unlock(&table->table_mutex);
// 	// printf("status after unlock: %d\n", status);
// }

void	*dinner_monitor(void *data) // new version
{
	t_table	*table;

	table = (t_table *) data;
	if (table->max_meal_count == 0)
	{
		printf("exit early max count = 0 \n");
		return (NULL);
	}

	set_bool(&table->table_mutex, &table->end_simulation,false);
	// printf("monitor thread running \n");
	// printf("pre true while loop\n");
	// sim_start_delay(table->start_time_in_ms + 10);
	// table->start_time_in_ms = gettime(MILLISECOND);
	sim_start_delay(table->start_time_in_ms + 10);// small delay to not immediately get busted by monitor
	while (true)
	{
		if (!are_all_philosophers_alive(table))
			return (NULL);
		if (simulation_finished(table))
			break;
		usleep(1000);
	}
	// printf("after true while loop\n");
	return (NULL);
	// int status = pthread_mutex_lock(&table->table_mutex);
	// printf("status after lock: %d\n", status);
	// table->end_simulation = false;
	// status = pthread_mutex_unlock(&table->table_mutex);
	// printf("status after unlock: %d\n", status);
}