/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: falamlih <falamlih@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/26 17:24:08 by falamlih          #+#    #+#             */
/*   Updated: 2026/07/31 01:26:15 by falamlih         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "headers.h"

void	*monitor(void *args)
{
	t_system		*system;
	unsigned int	i;
	long			burnouted;

	system = (t_system *)args;
	while (!system->stop)
	{
		i = 0;
		while (i < system->config.n_coders)
		{
			pthread_mutex_lock(&system->coders[i].mutex_coder);
			burnouted = system->coders[i].last_compile;
			pthread_mutex_unlock(&system->coders[i].mutex_coder);
			if (count_burnout(burnouted) >= system->config.t_burnout)
			{
				system->stop = true;
				pthread_cond_broadcast(&system->schedule.cond);
				burnout(&system->coders[i]);
				break ;
			}
			i++;
		}
		usleep(1000);
	}
	return (NULL);
}
