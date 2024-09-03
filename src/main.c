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
	if (table->max_meal_count == 0) // maybe just return false because there is also no monitorthread
		//running or change function to int and error handle that way
		return(printf("Number of limited meals is 0, nothing to do =)\n"), true);
	if (table->philo_nbr == 1)
	{
		// if (!safe_thread_handle(&table->philos[0].thread_id, lone_philo, &table->philos[0], CREATE))
			return (false);
	}
	else
	{
		while (i < table->philo_nbr)
		{
			if (!safe_thread_handle(&table->philos[i].thread_id, dinner_simulation, &table->philos[i], CREATE))
				return (false);
			i++;
		}
	}
	if (!safe_thread_handle(&table->monitor, dinner_monitor, table, CREATE))
		return (false);
	table->start_time_in_ms = gettime(MILLISECOND);
	// pthread_mutex_lock(&table->table_mutex);
	// table->all_threads_ready = true;
	// pthread_mutex_unlock(&table->table_mutex);
	set_bool(&table->table_mutex, &table->all_threads_ready, true);
	return (true);
}

static void	stop_dinner_simulation(t_table *table)
{
	size_t	i;

	i = 0;
	if (table->max_meal_count == 0)
	{
		cleanup_simulation(table);
		return;
	}
	while (i < table->philo_nbr)
	{
		safe_thread_handle(&table->philos[i].thread_id, NULL, NULL, JOIN);
		i++;
	}
	safe_thread_handle(&table->monitor, NULL, NULL, JOIN);
	// maybe set boolean to end simuluation
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
			// clean(&table);
		}
		else
			return (error_msg(STR_INVALID_INPUT_EXIT, -1));
	}
	else
		error_msg(STR_USAGE, -2);
	return (EXIT_SUCCESS);
}
