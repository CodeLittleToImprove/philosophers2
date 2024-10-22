/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbui-quo <tbui-quo@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/26 17:34:25 by tbui-quo          #+#    #+#             */
/*   Updated: 2024/06/26 17:34:25 by tbui-quo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../lib/philo.h"

bool	parse_and_validate_table_args(t_table *table, const int argc,
	char *argv[])
{
	int		i;
	long	parsed_value;

	i = 1;
	while (i < argc)
	{
		if (!is_valid_input(argv[i]))
			return (false);
		parsed_value = ft_atol(argv[i]);
		if (parsed_value == OVER_INT_MAX)
			return (false);
		i++;
	}
	table->philo_nbr = ft_atol(argv[1]);
	if (table->philo_nbr > 200)
		return (error_msg(TOO_MANY_PHILOS, false), false);
	table->time_to_die_in_ms = ft_atol(argv[2]);
	table->time_to_eat_in_ms = ft_atol(argv[3]);
	table->time_to_sleep_in_ms = ft_atol(argv[4]);
	if (argv[5])
		table->max_meal_count = ft_atol(argv[5]);
	else
		table->max_meal_count = -1;
	return (true);
}
