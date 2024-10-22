/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   getter_setter.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbui-quo <tbui-quo@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/14 18:00:08 by tbui-quo          #+#    #+#             */
/*   Updated: 2024/08/14 18:00:08 by tbui-quo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../lib/philo.h"

bool	get_bool(pthread_mutex_t *mutex, bool *value)
{
	bool	ret;

	safe_mutex_handle(mutex, LOCK, "bool_mutex_get");
	ret = *value;
	safe_mutex_handle(mutex, UNLOCK, "bool_mutex_get");
	return (ret);
}

void	set_bool(pthread_mutex_t *mutex, bool *dest, bool value)
{
	safe_mutex_handle(mutex, LOCK, "bool_mutex_set");
	*dest = value;
	safe_mutex_handle(mutex, UNLOCK, "bool_mutex_set");
}

time_t	get_time_t(pthread_mutex_t *mutex, time_t *value)
{
	time_t	ret;

	safe_mutex_handle(mutex, LOCK, "time_t_mutex_get");
	ret = *value;
	safe_mutex_handle(mutex, UNLOCK, "time_t_mutex_get");
	return (ret);
}

void	set_time_t(pthread_mutex_t *mutex, time_t *dest, time_t value)
{
	safe_mutex_handle(mutex, LOCK, "time_t_mutex_set");
	*dest = value;
	safe_mutex_handle(mutex, UNLOCK, "time_t_mutex_set");
}

long	get_long(pthread_mutex_t *mutex, long *value)
{
	time_t	ret;

	safe_mutex_handle(mutex, LOCK, "long_mutex_get");
	ret = *value;
	safe_mutex_handle(mutex, UNLOCK, "long_mutex_get");
	return (ret);
}
