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

void	set_bool(pthread_mutex_t *mutex, bool *dest, bool value)
{
	safe_mutex_handle(mutex, LOCK);
	*dest = value;
	safe_mutex_handle(mutex, UNLOCK);
}

bool	get_bool(pthread_mutex_t *mutex, bool *value)
{
	bool	ret;

	safe_mutex_handle(mutex, LOCK);
	ret = *value;
	safe_mutex_handle(mutex,UNLOCK);
	return (ret);
}
//
// long	get_long(pthread_mutex_t *mutex, long *value)
// {
// 	long	ret;
//
// 	safe_mutex_handle(mutex, LOCK);
// 	ret = *value;
// 	safe_mutex_handle(mutex,UNLOCK);
// 	return (ret);
// }
//
// void	set_long(pthread_mutex_t *mutex, long *dest, long value)
// {
// 	safe_mutex_handle(mutex, LOCK);
// 	*dest = value;
// 	safe_mutex_handle(mutex, UNLOCK);
// }