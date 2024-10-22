/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbui-quo <tbui-quo@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/14 17:47:33 by tbui-quo          #+#    #+#             */
/*   Updated: 2024/08/14 17:47:33 by tbui-quo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../lib/philo.h"

int	error_msg(const char *str, const int exit_nbr)
{
	printf(R "%s\n" RESET, str);
	return (exit_nbr);
}

void	cleanup_simulation(t_table *table)
{
	t_philo	*philo;
	size_t	i;

	i = 0;
	while (i < table->philo_nbr)
	{
		philo = table->philos + i;
		safe_mutex_handle(&philo->philo_mutex, DESTROY, "philo_mutex");
		i++;
	}
	safe_mutex_handle(&table->write_status_mutex, DESTROY, "write_mutex");
	safe_mutex_handle(&table->table_mutex, DESTROY, "table_mutex");
	free(table->forks);
	free(table->philos);
}
