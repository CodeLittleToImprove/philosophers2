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

void	data_init(t_table *table)
{
	size_t	i;

	i = 0;
	table->philos = (t_philo *) malloc(sizeof(t_philo) * table->philo_nbr);
	table->forks = (t_fork *) malloc(sizeof(t_fork) *table->philo_nbr);
	// free properly after a malloc fails!!
}
