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

static	void	assign_forks(t_philo *philo, t_fork *forks, size_t philo_position)
{
	int	philo_nbr;

	philo_nbr = philo->table->philo_nbr;
	philo->first_fork = &forks[(philo_position + 1) % philo_nbr];
	philo->second_fork = &forks[philo_position];
	if (philo->id % 2 == 0)
	{
		philo->first_fork = &forks[philo_position];
		philo->second_fork = &forks[(philo_position + 1) % philo_nbr];
	}
}

static	bool	philo_init(t_table *table)
{
	size_t	i;
	t_philo	*philo;

	i = 0;
	while (i < table->philo_nbr)
	{
		philo = &table->philos[i];
		philo->id = i + 1;
		philo->table = table;
		if (!safe_mutex_handle(&philo->philo_mutex, INIT))
			return (false);
		assign_forks(philo, table->forks, i);
		i++;
	}
	return (true);
}

bool	data_init(t_table *table)
{
	if (!allocate_philos_and_forks(table))
		return (false);
	if (table->forks == NULL) // because of clion tells me that
		return (false);
	if (!init_all_mutexes(table))
		return (false);
	if (!philo_init(table))
		return (false);
	return (true);
}
