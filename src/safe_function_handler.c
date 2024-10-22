/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   safe_function_handler.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbui-quo <tbui-quo@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/18 14:35:47 by tbui-quo          #+#    #+#             */
/*   Updated: 2024/10/18 16:42:22 by tbui-quo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../lib/philo.h"

void	*safe_malloc(size_t bytes)
{
	void	*ret;

	ret = malloc(bytes);
	if (ret == NULL)
		printf(R "Error with malloc: Could not allocate memory.\n" RESET);
	memset(ret, 0, bytes);
	return (ret);
}

static	void	handle_mutex_error(int status, t_opcode opcode)
{
	const char	*error_message;

	error_message = "Unexpected error, no clue";
	if (status == 0)
		return ;
	if ((status == EINVAL && (opcode == LOCK || opcode == UNLOCK
				|| opcode == DESTROY)))
		error_message = "The value specified by mutex is invalid.";
	else if (status == EINVAL && opcode == INIT)
		error_message = "The value specified by attr is invalid.";
	else if (status == EDEADLK)
		error_message = "A deadlock occur if thread blocked waiting for mutex.";
	else if (status == EPERM)
		error_message = "The current thread does not hold a lock on mutex.";
	else if (status == ENOMEM)
		error_message = "Process cannot allocate memory to create mutex.";
	else if (status == EBUSY)
		error_message = "Mutex is locked.";
	printf(R "%s\n" RESET, error_message);
}

bool	safe_mutex_handle(pthread_mutex_t *mutex, t_opcode opcode,
	const char *mutex_name)
{
	int	status;

	status = 0;
	if (opcode == LOCK)
		status = pthread_mutex_lock(mutex);
	else if (opcode == UNLOCK)
		status = pthread_mutex_unlock(mutex);
	else if (opcode == INIT)
		status = pthread_mutex_init(mutex, NULL);
	else if (opcode == DESTROY)
		status = pthread_mutex_destroy(mutex);
	if (status != 0)
	{
		printf("faulty mutex name is %s\n", mutex_name);
		handle_mutex_error(status, opcode);
		return (false);
	}
	return (true);
}

static	void	handle_thread_error(int status, t_opcode opcode)
{
	const char	*error_message;

	error_message = "Unexpected error, no clue";
	if (status == 0)
		return ;
	if (status == EAGAIN)
		error_message = "Insufficient ressources to create another thread";
	else if (status == EPERM)
		error_message = "The caller does not have appropriate permission ";
	else if (status == EINVAL && opcode == CREATE)
		error_message = "The value specified by attr is invalid";
	else if ((status == EINVAL && opcode == JOIN) || opcode == DETACH)
		error_message = "The value specified by threads is not joinable";
	else if (status == ESRCH)
		error_message = "No thread could be found corresponding to that"
			"specified by the given thread ID, thread.";
	else if (status == EDEADLK)
		error_message = "A deadlock was detected or the value of"
			"thread specifies the calling thread.";
	printf(R "%s\n" RESET, error_message);
}

bool	safe_thread_handle(pthread_t *thread, void *(*foo)(void*),
	void *data, t_opcode opcode)
{
	int	status;

	status = 0;
	if (opcode == CREATE)
		status = pthread_create(thread, NULL, foo, data);
	else if (opcode == JOIN)
		status = pthread_join(*thread, NULL);
	else if (opcode == DETACH)
		status = pthread_detach(*thread);
	else
		printf("Wrong opcode for thread_handle: use <CREATE> <JOIN> <DETACH>,"
			"aka not possible");
	if (status != 0)
	{
		handle_thread_error(status, opcode);
		return (false);
	}
	return (true);
}
