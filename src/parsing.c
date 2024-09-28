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

static	bool	is_space(const char c)
{
	return ((c >= 9 && c <= 13) || c == ' ');
}

static	bool	is_digit(const char c)
{
	return (c >= '0' && c <= '9');
}

static const char	*get_number_start(const char *str)
{
	while (is_space(*str))
		str++;
	if (*str == '+')
		str++;
	if (*str == '-' || !is_digit(*str))
		return (NULL);
	return (str);
}

static bool	is_valid_input(const char *str)
{
	int	len;

	len = 0;
	while (is_space(*str))
		str++;
	if (*str == '+')
		str++;
	else if (*str == '-')
		return (error_msg(STR_ERR_INPUT_DIGIT, false));
	if (!is_digit(*str))
		return (error_msg(STR_ERR_NO_DIGIT, false));
	while (is_digit(*str))
	{
		if (++len > 10)
			return (error_msg(STR_ERR_OVER_INT_MAX, false));
		str++;
	}
	return (true);
}

static	long	ft_atol(const char *str)
{
	long	num;

	num = 0;
	str = get_number_start(str);
	while (is_digit(*str))
	{
		if (num > (INT_MAX / 10) ||
			(num == (INT_MAX / 10) && (*str - '0') > 7))
				return (error_msg(STR_ERR_OVER_INT_MAX, false), -1);
		num = (num * 10) + (*str++ - '0');
	}
	return (num);
}

bool	parse_and_validate_table_args(t_table *table, const int argc, char *argv[])
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
	if((table->philo_nbr = ft_atol(argv[1])) > 200)
		return (error_msg(TOO_MANY_PHILOS, false), false);
	table->time_to_die_in_ms = ft_atol(argv[2]);
	table->time_to_eat_in_ms = ft_atol(argv[3]);
	table->time_to_sleep_in_ms = ft_atol(argv[4]);
	if (argv[5])
		table->max_meal_count = ft_atol(argv[5]);
	else
		table->max_meal_count = -1;
	// printf("Number of philosophers: %ld\n", table->philo_nbr);
	// printf("Time to die (ms): %ld\n", table->time_to_die_in_ms);
	// printf("Time to eat (ms): %ld\n", table->time_to_eat_in_ms);
	// printf("Time to sleep (ms): %ld\n", table->time_to_sleep_in_ms);
	// printf("Number of meals limit: %ld\n", table->nbr_limit_meals);
	return (true);
}
