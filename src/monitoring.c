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

void	*monitoring_dinner(void *data)
{
	return (NULL);
}