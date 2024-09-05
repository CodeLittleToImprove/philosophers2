/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbui-quo <tbui-quo@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/23 16:20:22 by tbui-quo          #+#    #+#             */
/*   Updated: 2024/08/23 16:20:22 by tbui-quo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../lib/philo.h"

// long	gettime(t_time_code time_code)
// {
// 	struct timeval	tv;
//
// 	if (gettimeofday(&tv, NULL))
// 		error_exit("Gettimeofday failed");
// 	if (time_code == SECOND)
// 		return (tv.tv_sec + (tv.tv_usec / 1e6));
// 	else if (time_code == MILLISECOND)
// 		return (tv.tv_sec * 1e3 + (tv.tv_usec / 1e3));
// 	else if (time_code == MICROSECOND)
// 		return (tv.tv_sec * 1e6 + tv.tv_usec);
// 	else
// 		error_exit("Wrong input to gettime!");
// 	return (0);
// }
// Seconds: sec
// Milliseconds: ms
// Microseconds: usec

time_t	gettime(t_time_code time_code)
{
	struct timeval		tv;

	if (gettimeofday(&tv, NULL) == -1)
		return (printf(R "Error with gettimeofday\n" RESET),-1);
	if (time_code == SECOND)
		return (tv.tv_sec + (tv.tv_usec / 1e6));
	else if (time_code == MILLISECOND)
		return (tv.tv_sec * 1e3 + (tv.tv_usec / 1e3));
	else if (time_code == MICROSECOND)
		return (tv.tv_sec * 1e6 + tv.tv_usec);
	else
		printf(R "Wrong input to gettime!\n" RESET);
	return (0);
}

void	wait_until_all_threads_ready(t_table *table)
{
	while (!get_bool(&table->table_mutex, &table->all_threads_ready))
		// usleep(ONE_SECOND_IN_MS); // maybe buggy lets see
			usleep(100);
}

void	sim_start_delay(time_t start_time)
{
	while (gettime(MILLISECOND) < start_time)
		continue ;
}

// void	precise_usleep(time_t sleep_time_ms, t_table *table) // buggy cause to be too fast
// {
// 	time_t	start_time_usec;
// 	time_t	sleep_time_usec;
// 	time_t	time_passed_usec;
// 	time_t	remaining_time_in_usec;
//
// 	start_time_usec = gettime(MICROSECOND);
// 	sleep_time_usec = sleep_time_ms / 1e3;
//
// 	while (gettime(MICROSECOND) - start_time_usec < sleep_time_usec)
// 	{
// 		if (simulation_finished(table))
// 			break ;
// 		time_passed_usec = gettime(MICROSECOND) - start_time_usec;
// 		remaining_time_in_usec = sleep_time_usec - time_passed_usec;
// 		if (remaining_time_in_usec > ONE_SECOND_IN_MS)
// 			usleep(remaining_time_in_usec / 2);
// 		else
// 		{
// 			while (gettime(MICROSECOND) - start_time_usec < sleep_time_usec)
// 				;
// 		}
// 	}
// }

void	precise_usleep(time_t sleep_time, t_table *table)
{
	time_t	wake_up;

	wake_up = gettime(MILLISECOND) + sleep_time;
	while (gettime(MILLISECOND) < wake_up)
	{
		if (simulation_finished(table))
			break ;
		usleep(100);
	}
}