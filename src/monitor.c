/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: falamlih <falamlih@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/26 17:24:08 by falamlih          #+#    #+#             */
/*   Updated: 2026/08/01 16:11:43 by falamlih         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "headers.h"

void	*monitor(void *args)
{
	t_system		*system;
	unsigned int	i;
	long			burnouted;
	unsigned int	end;

	system = (t_system *)args;
	end = 0;
	while (!system_is_stopped(system))
	{
		i = 0;
		while (i < system->config.n_coders)
		{
			if (system->coders[i].compile_count == system->config.compiles_required)
				end++;
			pthread_mutex_lock(&system->coders[i].mutex_coder);
			burnouted = system->coders[i].last_compile;
			pthread_mutex_unlock(&system->coders[i].mutex_coder);
			if (count_burnout(burnouted) >= system->config.t_burnout)
			{
				system_stop(system);
				pthread_mutex_lock(&system->schedule.mutex);
				pthread_cond_broadcast(&system->schedule.cond);
				pthread_mutex_unlock(&system->schedule.mutex);
				burnout(&system->coders[i]);
				break ;
			}
			i++;
		}
		if (end == system->config.n_coders)
			return (system_stop(system), NULL);
		usleep(1000);
	}
	return (NULL);
}
