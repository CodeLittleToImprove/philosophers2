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
int	error_exit(const char *error, ErrorLevel error_level)
{
	printf(R "%s\n" RESET, error);
	if (error_level == ERROR_CRITICAL)
	{
		printf(R "Program tries to exits safely\n" RESET, error);
		return (-2);
	}
	else if (error_level == ERROR_MINOR)
		return (-1);
	else
		return (0);
}
