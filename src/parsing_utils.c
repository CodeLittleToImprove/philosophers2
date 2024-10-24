/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbui-quo <tbui-quo@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/18 16:25:23 by tbui-quo          #+#    #+#             */
/*   Updated: 2024/10/18 16:25:23 by tbui-quo         ###   ########.fr       */
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

bool	is_valid_input(const char *str)
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

long	ft_atol(const char *str)
{
	long	num;

	num = 0;
	str = get_number_start(str);
	while (is_digit(*str))
	{
		if (num > (INT_MAX / 10)
			|| (num == (INT_MAX / 10) && (*str - '0') > 7))
			return (error_msg(STR_ERR_OVER_INT_MAX, false), -1);
		num = (num * 10) + (*str++ - '0');
	}
	return (num);
}
