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

static bool	setup_dinner_simulation(t_table *table)
{
	// initialize philosophers threads and monitor thread
	size_t	i;

	i = 0;
	if (table->nbr_limit_meals == 0)
		return(printf("Number of limited meals is 0, nothing to do =)\n"), true);
	if (table->philo_nbr == 1)
	{
		// printf("Only one philosopher, creating lone philosopher thread.\n");
		if (!safe_thread_handle(&table->philos[0].thread_id, lone_philo, &table->philos[0], CREATE))
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
	if (!safe_thread_handle(&table->monitor, dinner_monitor, &table->philos[0], CREATE))
		return (false);
	table->start_time_in_ms = gettime(MILLISECOND);
	i = 0;
	while (i < table->philo_nbr)
	{
		if(!safe_thread_handle(&table->philos[i].thread_id, NULL, NULL, JOIN))
			return (false);
		i++;
	}
	safe_thread_handle(&table->monitor, NULL, NULL, JOIN);
	return (true);
}

int	main(const int argc, char *argv[])
{
	t_table	table;

	if (argc == 5 || argc == 6)
	{
		if (parse_input(&table, argc, argv))
		{
			data_init(&table); // destroy mutexes and free memory when fail
			setup_dinner_simulation(&table);
			// dinner_start(&table);
			clean(&table);
		}
		else
			return (error_msg(STR_INVALID_INPUT_EXIT, -1));
	}
	else
		error_msg(STR_USAGE, -2);
	return (0);
}
