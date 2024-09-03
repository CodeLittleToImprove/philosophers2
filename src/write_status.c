/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   write_status.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbui-quo <tbui-quo@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/09 18:14:53 by tbui-quo          #+#    #+#             */
/*   Updated: 2024/07/09 18:14:53 by tbui-quo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// ReSharper disable All
#include "../lib/philo.h"

static void write_status_debug(t_philo_status status, t_philo *philo, long elapsed)
{
	if (status == TAKE_FIRST_FORK && !simulation_finished(philo->table))
		printf(W"%6ld"RESET" %d has taken the 1° fork"
		"\t\t\tn°"B"[ fork_id:%d ]\n"RESET, elapsed, philo->id,
		philo->first_fork->fork_id);
		else if (status == TAKE_SECOND_FORK && !simulation_finished(philo->table))
		printf(W"%6ld"RESET" %d has taken the 2° fork"
		"\t\t\tn°"B"[ fork_id:%d ]\n"RESET, elapsed, philo->id,
		philo->second_fork->fork_id);
		else if (status == EATING && !simulation_finished(philo->table))
		printf(W"%6ld"C" %d is eating"
		"\t\t\t"Y"[ meal_nbr:%ld ]\n"RESET, elapsed, philo->id, philo->times_ate);
		else if (status == SLEEPING && !simulation_finished(philo->table))
			printf(W"%6ld"Y" %d is sleeping\n", elapsed, philo->id);
		else if (status == THINKING && !simulation_finished(philo->table))
			printf(W"%6ld"G" %d is thinking\n", elapsed, philo->id);
		else if (status == DIED)
			printf(W"%6ld"R" %d died\n"RESET, elapsed, philo->id);
}

void	write_status(t_philo_status status, t_philo *philo, bool debug)
{
	long	elapsed;

	elapsed = gettime(MILLISECOND) - philo->table->start_time_in_ms;
	// if(philo->full)
	// 	return;
	safe_mutex_handle(&philo->table->write_status_mutex, LOCK, "write_status+mutex");
	if (debug == true)
	{
		write_status_debug(status, philo, elapsed);
	}
	else
		if (((status == TAKE_FIRST_FORK) || (status == TAKE_SECOND_FORK))
			&& !simulation_finished(philo->table))
			printf(W"%-6ld"RESET"%d has taken a fork \n", elapsed, philo->id);
		else if (status == EATING && !simulation_finished(philo->table))
			printf(W"%-6ld"C"%d is eating "RESET"\n", elapsed, philo->id);
		else if (status == SLEEPING && !simulation_finished(philo->table))
			printf(W"%-6ld"Y"%d is sleeping "RESET"\n", elapsed, philo->id);
		else if (status == THINKING && !simulation_finished(philo->table))
			printf(W"%-6ld"G"%d is thinking "RESET"\n", elapsed, philo->id);
		else if (status == DIED)
			printf(W"%-6ld"R"%d died\n"RESET, elapsed, philo->id);
	safe_mutex_handle(&philo->table->write_status_mutex, UNLOCK, "write_status+mutex");
}