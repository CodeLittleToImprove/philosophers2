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

static bool	setup_dinner_simulation(t_table *table)
{
	size_t	i;

	i = 0;
	if (table->max_meal_count == 0)
		return(printf("Number of limited meals is 0, nothing to do =)\n"), false);
	table->start_time_in_ms = gettime(MILLISECOND);
	if (table->philo_nbr == 1)
	{
		// if (!safe_thread_handle(&table->philos[0].thread_id, lone_philo, &table->philos[0], CREATE))
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
	// table->start_time_in_ms = gettime(MILLISECOND);
	sim_start_delay(table->start_time_in_ms);
	if (!safe_thread_handle(&table->monitor, dinner_monitor, table, CREATE)) // cause for valgrind fail without it i don't get busted
	{
		printf("failed to create monitor thread \n");
		return (false);
	}

	// int ret = pthread_create(&table->monitor, NULL, dinner_monitor, (void *) table);
	// if (ret != 0)
	// {
	// 	printf("Failed to create monitor thread, error code: %d, message: %s\n", ret, strerror(ret));
	// }


	// table->start_time_in_ms = gettime(MILLISECOND);
	// pthread_mutex_lock(&table->table_mutex);
	// table->all_threads_ready = true;
	// pthread_mutex_unlock(&table->table_mutex);
	set_bool(&table->table_mutex, &table->all_threads_ready, true);
	// printf("returned true \n");
	return (true);
}

static void	stop_dinner_simulation(t_table *table) // original
{
	size_t	i;

	i = 0;
	// if (table->max_meal_count == 0) // double
	// {
	// 	cleanup_simulation(table);
	// 	return;
	// }
	while (i < table->philo_nbr)
	{
		safe_thread_handle(&table->philos[i].thread_id, NULL, NULL, JOIN);
		i++;
	}
	safe_thread_handle(&table->monitor, NULL, NULL, JOIN);
	// maybe set boolean to end simuluation
}

// static void	stop_dinner_simulation(t_table *table) // test
// {
// 	size_t	i;
//
// 	i = 0;
// 	// if (table->max_meal_count == 0) // double
// 	// {
// 	// 	cleanup_simulation(table);
// 	// 	return;
// 	// }
// 	while (i < table->philo_nbr)
// 	{
// 		pthread_join(table->philos[i].thread_id, NULL);
// 		i++;
// 	}
// 	// printf("joined all philo threads\n");
// 	pthread_join(table->monitor, NULL);
// 	// maybe set boolean to end simuluation
// }

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
