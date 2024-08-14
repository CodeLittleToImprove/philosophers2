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
		parse_input(&table, argv);
		data_init(&table);
		dinner_start(&table);
		clean(&table);
	}
	else
		error_exit("Wrong input:\n"G"Correct is .philo 5 800 200 200 [5]", ERROR_MINOR);
	return (0);
}