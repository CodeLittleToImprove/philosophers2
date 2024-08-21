/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   data_init.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbui-quo <tbui-quo@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/17 15:45:50 by tbui-quo          #+#    #+#             */
/*   Updated: 2024/08/17 15:45:50 by tbui-quo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../lib/philo.h"

static	bool	init_all_mutexes(t_table *table)
{
	size_t	i;

	i = 0;
	if (!safe_mutex_handle(&table->write_status_mutex, INIT))
		return (false);
	if (!safe_mutex_handle(&table->table_mutex, INIT))
		return (false);
	while (i < table->philo_nbr)
	{
		if (!safe_mutex_handle(&table->forks[i].fork_mutex, INIT))
			return (false);
		table->forks[i].fork_id = i;
		i++;
	}
	return (true);
}

static	bool	allocate_philos_and_forks(t_table *table)
{
	size_t	i;

	i = 0;
	table->philos = safe_malloc(sizeof(t_philo) * table->philo_nbr);
	if (table->philos == NULL)
		return (false);
	table->forks = safe_malloc(sizeof(t_fork) * table->philo_nbr);
	if (table->forks == NULL)
	{
		free(table->philos);
		table->philos = NULL;
		return (false);
	}
	return (true);
}

bool	data_init(t_table *table)
{
	// table->philos = safe_malloc(sizeof(t_philo) * table->philo_nbr);
	// if (table->philos == NULL)
	// 	return (false);
	// table->forks = safe_malloc(sizeof(t_fork) * table->philo_nbr);
	// if (table->forks == NULL)
	// {
	// 	free(table->philos);
	// 	return (false);
	// }
	if (table == NULL)
		return false;
	if (!allocate_philos_and_forks(table))
		return (false);
	// if(!(safe_mutex_handle(&table->write_status_mutex, INIT))) //maybe initialize all mutex in one go?
	// 	return false;
	// if(!(safe_mutex_handle(&table->table_mutex, INIT)))
	// 	return false;
	if (!init_all_mutexes(table))
		return (false);
	// continue with philo init
	return (true);
}
