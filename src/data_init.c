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
	if (!safe_mutex_handle(&table->write_status_mutex, INIT, "write_mutex"))
		return (false);
	if (!safe_mutex_handle(&table->table_mutex, INIT, "table_mutex"))
		return (false);
	while (i < table->philo_nbr)
	{
		if (!safe_mutex_handle(&table->forks[i].fork_mutex, INIT, "fork_mutex"))
			return (false);
		table->forks[i].fork_id = i;
		i++;
	}
	return (true);
}

static	void	assign_forks(t_philo *philo,
t_fork *forks, size_t philo_position)
{
	int	philo_nbr;

	philo_nbr = philo->table->philo_nbr;
	if (philo->id % 2 == 1)
	{
		// printf("odd philo id: %d\n", philo->id);
		// int temp = (philo_position + 1) % philo_nbr;
		// int temp2 = philo_position;
		philo->first_fork = &forks[(philo_position + 1) % philo_nbr];
		// printf("philo_first fork %d \n", temp);
		philo->second_fork = &forks[philo_position];
		// printf("philo_second fork %d \n", temp2);
	}
	if (philo->id % 2 == EVEN)
	{
		// int temp = philo_position;
		// int temp2 = (philo_position + 1) % philo_nbr;
		// printf("even philo id: %d\n", philo->id);
		philo->first_fork = &forks[philo_position];
		// printf("philo_first fork %d \n", temp);
		philo->second_fork = &forks[(philo_position + 1) % philo_nbr];
		// printf("philo_second fork %d \n", temp2);
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
		philo->alive = true;
		philo->id = i + 1;
		philo->table = table;
		philo->last_meal_time_ms = gettime(MILLISECOND);
		if (!safe_mutex_handle(&philo->philo_mutex, INIT, "philo_mutex"))
			return (false);
		assign_forks(philo, table->forks, i);
		i++;
	}
	return (true);
}

bool	data_init(t_table *table)
{
	table->end_simulation = false;
	table->all_threads_ready = false;
	if (!allocate_philos_and_forks(table))
		return (false);
	if (table->forks == NULL)
		return (false);
	if (!init_all_mutexes(table))
		return (false);
	if (!philo_init(table))
		return (false);
	return (true);
}
