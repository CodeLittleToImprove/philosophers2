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
		num = (num * 10) + (*str++ - '0');
	if (num > INT_MAX)
		return (error_msg(STR_ERR_OVER_INT_MAX, false));
	return (num);
}

bool	parse_and_validate_table_args(t_table *table, const int argc, char *argv[])
{
	bool	valid_input;
	int		i;

	valid_input = false;
	i = 1;
	while (i < argc)
	{
		valid_input = is_valid_input(argv[i]);
		if (!valid_input)
			return (false);
		i++;
	}
	table->philo_nbr = ft_atol(argv[1]);
	table->time_to_die_in_ms = ft_atol(argv[2]);
	table->time_to_eat_in_ms = ft_atol(argv[3]);
	table->time_to_sleep_in_ms = ft_atol(argv[4]);
	// if (table->time_to_die_in_usec < MIN_TIME_IN_MILLISECONDS
	// 	|| table->time_to_eat_in_usec < MIN_TIME_IN_MILLISECONDS
	// 	|| table->time_to_sleep_in_usec < MIN_TIME_IN_MILLISECONDS)
	// 	error_exit("Use timestamps greater than 60000 usec", ERROR_MINOR);
	if (argv[5])
		table->nbr_limit_meals = ft_atol(argv[5]);
	else
		table->nbr_limit_meals = -1;
	printf("Number of philosophers: %ld\n", table->philo_nbr);
	printf("Time to die (ms): %ld\n", table->time_to_die_in_ms);
	printf("Time to eat (ms): %ld\n", table->time_to_eat_in_ms);
	printf("Time to sleep (ms): %ld\n", table->time_to_sleep_in_ms);
	printf("Number of meals limit: %ld\n", table->nbr_limit_meals);
	return (true);
}
