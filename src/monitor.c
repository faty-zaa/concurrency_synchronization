/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: falamlih <falamlih@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/26 17:24:08 by falamlih          #+#    #+#             */
/*   Updated: 2026/08/08 22:20:06 by falamlih         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "headers.h"

bool	check_burnout(t_system *system)
{
	unsigned int	i;
	long			now;
	unsigned int	count;

	i = 0;
	while (i < system->config.n_coders)
	{
		pthread_mutex_lock(&system->coders[i].mutex_coder);
		now = get_time_ms() - system->starting_time;
		count = system->coders[i].compile_count;
		if (now >= system->coders[i].deadline
			&& count < system->config.compiles_required)
		{
			pthread_mutex_unlock(&system->coders[i].mutex_coder);
			burnout(&system->coders[i]);
			return (true);
		}
		pthread_mutex_unlock(&system->coders[i].mutex_coder);
		i++;
	}
	return (false);
}

void	wake_all_dongles(t_system *system)
{
	unsigned int	i;

	i = 0;
	while (i < system->config.n_coders)
	{
		pthread_mutex_lock(&system->dongles[i].mutex_dongle);
		pthread_cond_broadcast(&system->dongles[i].cond_dongle);
		pthread_mutex_unlock(&system->dongles[i].mutex_dongle);
		i++;
	}
}

unsigned int	coder_compiles(t_coder *coder)
{
	unsigned int	count;

	pthread_mutex_lock(&coder->mutex_coder);
	count = coder->compile_count;
	pthread_mutex_unlock(&coder->mutex_coder);
	return (count);
}

bool	all_coders_compile(t_system *system)
{
	unsigned int	i;
	unsigned int	count;

	i = 0;
	while (i < system->config.n_coders)
	{
		count = system->config.compiles_required;
		if (coder_compiles(&system->coders[i]) < count)
			return (false);
		i++;
	}
	return (true);
}

void	*monitor(void *arg)
{
	t_system	*system;

	system = (t_system *)arg;
	while (!system_is_stopped(system))
	{
		if (check_burnout(system) || all_coders_compile(system))
		{
			system_stop(system);
			wake_all_dongles(system);
			break ;
		}
		usleep(1000);
	}
	return (NULL);
}
