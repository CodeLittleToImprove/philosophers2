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

// int	error_exit(const char *error, ErrorLevel error_level)
// {
// 	printf(R "%s\n" RESET, error);
// 	if (error_level == ERROR_CRITICAL)
// 	{
// 		printf(R "Program tries to exits safely\n" RESET);
// 		return (-2);
// 	}
// 	else if (error_level == ERROR_MINOR)
// 		return (-1);
// 	else
// 		return (0);
// }
// int	msg(char *str, char *detail, int exit_no)
// {
// 	if (!detail)
// 		printf(str, STR_PROG_NAME);
// 	else
// 		printf(str, STR_PROG_NAME, detail);
// 	return (exit_no);
// }

int	error_msg(const char *str, int exit_nbr)
{
	printf(R "%s\n" RESET, str);
	return (exit_nbr);
}

void	clean(t_table *table)
{
	t_philo	*philo;
	size_t	i;

	i = 0;
	while (i < table->philo_nbr)
	{
		philo = table->philos + 1;
		safe_mutex_handle(&philo->philo_mutex, DESTROY);
		i++;
	}
	safe_mutex_handle(&table->write_status_mutex, DESTROY);
	safe_mutex_handle(&table->table_mutex, DESTROY);
	free(table->forks);
	free(table->philos);
}

/* error_failure:
*	Frees any allocated memory, prints an error message and
*	returns 0 to indicate failure.
*	Used for error management during initialization.
*/
// int	error_failure(char *str, char *details, t_table *table)
// {
// 	if (table != NULL)
// 		free_table(table);
// 	return (error_msg(str, details, 0));
// }

/* error_null:
*	Frees any allocated memory, prints an error message and returns a NULL pointer.
*	Used for error management during initialization.
*/
// void	*error_null(char *str, char *details, t_table *table)
// {
// 	if (table != NULL)
// 		free_table(table);
// 	error_msg(str, details, EXIT_FAILURE);
// 	return (NULL);
// }