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

void	*dinner_monitor(void *data)
{
	t_table	*table;

	table = (t_table *) data;
	set_bool(&table->table_mutex, &table->end_simulation, false);
	sim_start_delay(table->start_time_in_ms + DELAY_TO_PREVENT_BUST);
	while (true)
	{
		if (!are_all_philosophers_alive(table))
			return (NULL);
		if (simulation_finished(table))
			break ;
		usleep(1000);
	}
	return (NULL);
}
