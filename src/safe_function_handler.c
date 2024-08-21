// /* ************************************************************************** */
// /*                                                                            */
// /*                                                        :::      ::::::::   */
// /*   safe_function_handler.c                            :+:      :+:    :+:   */
// /*                                                    +:+ +:+         +:+     */
// /*   By: tbui-quo <tbui-quo@student.1337.ma>        +#+  +:+       +#+        */
// /*                                                +#+#+#+#+#+   +#+           */
// /*   Created: 2024/07/09 17:59:46 by tbui-quo          #+#    #+#             */
// /*   Updated: 2024/07/09 17:59:46 by tbui-quo         ###   ########.fr       */
// /*                                                                            */
// /* ************************************************************************** */
//
#include "../lib/philo.h"
//
// void	*safe_malloc(size_t bytes)
// {
// 	void	*ret;
//
// 	ret = malloc(bytes);
// 	if (ret == NULL)
// 		error_exit("Error with the malloc", ERROR_CRITICAL);
// 	return (ret);
// }
//

void	*safe_malloc(size_t bytes)
{
	void	*ret;
	ret = malloc(bytes);
	if (ret == NULL)
		printf(R "Error with malloc: Could not allocate memory.\n" RESET);
	return (ret);
}

static	bool	handle_mutex_error(int status, t_opcode opcode)
{
	const char *error_message;
	if (status == 0)
		return (0);
	error_message = "Unexpected error, no clue";
	if ((status == EINVAL && (opcode == LOCK || opcode == UNLOCK
		|| opcode == DESTROY)))
		error_message = "The value specified by mutex is invalid.";
	else if (status == EINVAL && opcode == INIT)
		error_message = "The value specified by attr is invalid.";
	else if (status == EDEADLK)
		error_message = "A deadlock would occur if thread blocked waiting for mutex.";
	else if (status == EPERM)
		error_message = "The current thread does not hold a lock on mutex.";
	else if (status == ENOMEM)
		error_message = "The process cannot allocate enough memory to create another mutex.";
	else if (status == EBUSY)
		error_message = "Mutex is locked.";
	printf(R "%s\n" RESET, error_message);
	return (true);
}

//
bool	safe_mutex_handle(pthread_mutex_t *mutex, t_opcode opcode)
{
	int status = 0;

	if (opcode == LOCK)
		status = pthread_mutex_lock(mutex);
	else if (opcode == UNLOCK)
		status = pthread_mutex_unlock(mutex);
	else if (opcode == INIT)
		status = pthread_mutex_init(mutex, NULL);
	else if (opcode == DESTROY)
		status = pthread_mutex_destroy(mutex);
	return handle_mutex_error(status, opcode) == false;
}
//
// static	void	handle_thread_error(int status, t_opcode opcode)
// {
// 	if (status == 0)
// 		return ;
// 	if (status == EAGAIN)
// 		error_exit("Insufficient ressources to create another thread", ERROR_CRITICAL);
// 	else if (status == EPERM)
// 		error_exit("The caller does not have appropriate permission \n", ERROR_CRITICAL);
// 	else if (status == EINVAL && opcode == CREATE)
// 		error_exit("The value specified by attr is invalid", ERROR_CRITICAL);
// 	else if ((status == EINVAL && opcode == JOIN) || opcode == DETACH)
// 		error_exit("The value specified by threads is not joinable \n", ERROR_CRITICAL);
// 	else if (status == ESRCH)
// 		error_exit("No thread could be found corresponding to that"
// 			"specified by the given thread ID, thread.", ERROR_CRITICAL);
// 	else if (status == EDEADLK)
// 		error_exit("A deadlock was detected oor the value of"
// 			"thread specifies the calling thread.", ERROR_CRITICAL);
// }
//
// void safe_thread_handle(pthread_t *thread, void *(*foo)(void*), void *data, t_opcode opcode)
// {
// 	int status;
//
// 	if (opcode == CREATE)
// 	{
// 		if (thread == NULL || foo == NULL)
// 			error_exit("Null pointer passed for thread creation.", ERROR_CRITICAL);
// 		status = pthread_create(thread, NULL, foo, data);
// 		handle_thread_error(status, opcode);
// 		// printf("Thread created: %ld\n", (long)*thread);  // Added logging for thread creation
// 	}
// 	else if (opcode == JOIN)
// 	{
// 		if (thread == NULL)
// 			error_exit("Null pointer passed for thread join.", ERROR_CRITICAL);
// 		status = pthread_join(*thread, NULL);
// 		handle_thread_error(status, opcode);
// 		// printf("Thread joined: %ld\n", (long)*thread);  // Added logging for thread joining
// 	}
// 	else if (opcode == DETACH)
// 	{
// 		if (thread == NULL)
// 			error_exit("Null pointer passed for thread detach.", ERROR_CRITICAL);
// 		status = pthread_detach(*thread);
// 		handle_thread_error(status, opcode);
// 		// printf("Thread detaching: %ld\n", (long)*thread);  // Added logging for thread detaching
// 	}
// 	else
// 		error_exit("Wrong opcode for thread_handle: use <CREATE> <JOIN> <DETACH>", ERROR_CRITICAL);
// }
//
