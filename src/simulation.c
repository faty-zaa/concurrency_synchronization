/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: falamlih <falamlih@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/22 19:00:51 by falamlih          #+#    #+#             */
/*   Updated: 2026/08/07 23:25:09 by falamlih         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "headers.h"

void	log_print(t_coder *coder, const char *msg)
{
	pthread_mutex_lock(&coder->system->print_mutex);
	printf("%ld %d %s\n", get_time(coder->system), coder->coder_id, msg);
	pthread_mutex_unlock(&coder->system->print_mutex);
}

void	ft_sleep(long ms, t_coder *coder)
{
	while (get_time_ms() < ms)
	{
		usleep(1000);
		if (system_is_stopped(coder->system))
			break ;
	}
}

void	system_stop(t_system *system)
{
	pthread_mutex_lock(&system->stop_mutex);
	system->stop = true;
	pthread_mutex_unlock(&system->stop_mutex);
}

bool	system_is_stopped(t_system *system)
{
	bool	stopped;

	pthread_mutex_lock(&system->stop_mutex);
	stopped = system->stop;
	pthread_mutex_unlock(&system->stop_mutex);
	return (stopped);
}

void	*simulation(void *args)
{
	t_coder	*coder;

	coder = (t_coder *)args;
	while (!system_is_stopped(coder->system))
	{
		if (!take_dongles(coder))
			break ;
		compiling(coder);
		if (system_is_stopped(coder->system))
			break ;
		debugging(coder);
		if (system_is_stopped(coder->system))
			break ;
		refactoring(coder);
	}
	return (NULL);
}
