/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbui-quo <tbui-quo@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/14 18:04:07 by tbui-quo          #+#    #+#             */
/*   Updated: 2024/08/14 18:04:07 by tbui-quo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../lib/philo.h"

static void stop_dinner_simulation(t_table *table);

static bool	setup_dinner_simulation(t_table *table) // my opinion cleaner version
{
	size_t	i;

	i = 0;
	if (table->max_meal_count == 0)
		return(printf("Number of limited meals is 0, nothing to do =)\n"), false);
	table->start_time_in_ms = gettime(MILLISECOND);
	if (table->philo_nbr == 1)
	{
		if (!safe_thread_handle(&table->philos[0].thread_id, lone_philo, &table->philos[0], CREATE))
			return (false);
	}
	else
	{
		while (i < table->philo_nbr)
		{
			// printf("creating philosopher thread: %ld\n", i);
			if (!safe_thread_handle(&table->philos[i].thread_id, dinner_simulation, &table->philos[i], CREATE))
				return (false);
			i++;
		}
	}
	// printf("pre create monitor thread \n"); // could add a counter to the number of threads and wait for them all instead waiting some random amout
	sim_start_delay(table->start_time_in_ms);
	if (!safe_thread_handle(&table->monitor, dinner_monitor, table, CREATE)) // cause for valgrind fail without it i don't get busted
		return (false);
	set_bool(&table->table_mutex, &table->all_threads_ready, true);
	return (true);
}

// static bool	handle_single_philosopher(t_philo *philo);
// static bool	handle_multiple_philosophers(t_table *table);
//
// static bool	setup_dinner_simulation(t_table *table)
// {
// 	size_t	i;
//
// 	i = 0;
// 	if (table->max_meal_count == 0)
// 		return (printf("meal count is 0, nothing to do =)\n"), false);
// 	table->start_time_in_ms = gettime(MILLISECOND);
// 	if (table->philo_nbr == 1)
// 	{
// 		if (!handle_single_philosopher(&table->philos[0]))
// 			return (false);
// 	}
// 	else
// 	{
// 		if (!handle_multiple_philosophers(table))
// 			return (false);
// 	}
// 	sim_start_delay(table->start_time_in_ms);
// 	if (!safe_thread_handle(&table->monitor, dinner_monitor, table, CREATE))
// 		return (false);
// 	set_bool(&table->table_mutex, &table->all_threads_ready, true);
// 	return (true);
// }
//
// static bool	handle_single_philosopher(t_philo *philo)
// {
// 	if (!safe_thread_handle(&philo->thread_id,
// 			lone_philo, philo, CREATE))
// 		return (false);
// 	return (true);
// }
//
// static bool	handle_multiple_philosophers(t_table *table)
// {
// 	size_t	i;
//
// 	i = 0;
// 	while (i < table->philo_nbr)
// 	{
// 		if (!safe_thread_handle(&table->philos[i].thread_id,
// 				dinner_simulation, &table->philos[i], CREATE))
// 			return (false);
// 		i++;
// 	}
// 	return (true);
// }

static void	stop_dinner_simulation(t_table *table)
{
	size_t	i;

	i = 0;
	while (i < table->philo_nbr)
	{
		safe_thread_handle(&table->philos[i].thread_id, NULL, NULL, JOIN);
		i++;
	}
	safe_thread_handle(&table->monitor, NULL, NULL, JOIN);
}

int	main(const int argc, char *argv[])
{
	t_table	table;

	if (argc == 5 || argc == 6)
	{
		if (parse_and_validate_table_args(&table, argc, argv))
		{
			data_init(&table);
			if(!setup_dinner_simulation(&table))
			{
				cleanup_simulation(&table);
				return (EXIT_FAILURE);
			}
			stop_dinner_simulation(&table);
			cleanup_simulation(&table);
		}
		else
			return (error_msg(STR_INVALID_INPUT_EXIT, -1));
	}
	else
		error_msg(STR_USAGE, -2);
	return (EXIT_SUCCESS);
}
