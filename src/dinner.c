/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dinner.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbui-quo <tbui-quo@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/22 18:15:35 by tbui-quo          #+#    #+#             */
/*   Updated: 2024/08/22 18:15:35 by tbui-quo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../lib/philo.h"

// look how the other repo did it
// add this to philosophers creating

void	*dinner_simulation(void *data)
{
	t_philo *philo;

	philo = (t_philo *)data;

	wait_all_threads(philo->table);
	// maybe use getter setter but with time_t as datatype?
	pthread_mutex_lock(&philo->philo_mutex);
	philo->last_meal_time_ms = philo->table->start_time_in_ms;
	pthread_mutex_unlock(&philo->philo_mutex);
	return (NULL);
}