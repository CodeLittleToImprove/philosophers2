/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbui-quo <tbui-quo@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/14 18:04:07 by tbui-quo          #+#    #+#             */
/*   Updated: 2024/08/14 18:04:07 by tbui-quo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../lib/philo.h"

int	main(int argc, char *argv[])
{
	t_table	table;

	if (argc == 5 || argc == 6)
	{
		if (parse_input(&table, argc, argv))
		{
			data_init(&table); // destroy mutexes and free memory when fail
			// dinner_start(&table);
			clean(&table);
		}
		else
			return (error_msg(STR_INVALID_INPUT_EXIT, -1));
	}
	else
		error_msg(STR_USAGE, -2);
	return (0);
}
