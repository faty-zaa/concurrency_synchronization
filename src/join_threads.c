/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   join_threads.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: falamlih <falamlih@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/23 17:00:38 by falamlih          #+#    #+#             */
/*   Updated: 2026/08/03 06:35:34 by falamlih         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "headers.h"

void	cleanup_system(t_system *system)
{
	unsigned int	i;

	if (!system)
		return ;
	if (system->coders)
	{
		i = 0;
		while (i < system->config.n_coders)
		{
			pthread_mutex_destroy(&system->coders[i].mutex_coder);
			i++;
		}
		free(system->coders);
		system->coders = NULL;
	}
	if (system->dongles)
	{
		i = 0;
		while (i < system->config.n_coders)
		{
			pthread_mutex_destroy(&system->dongles[i].mutex_dongle);
			pthread_cond_destroy(&system->dongles[i].cond_dongle);
			if (strcmp(system->dongles[i].algo, "fifo") == 0)
				queue_destroy(&system->dongles[i].fifo);
			else if (strcmp(system->dongles[i].algo, "edf") == 0)
				heap_destroy(&system->dongles[i].edf);
			i++;
		}
		free(system->dongles);
		system->dongles = NULL;
	}
	pthread_mutex_destroy(&system->print_mutex);
	pthread_mutex_destroy(&system->stop_mutex);
}

void	join_threads(t_system *system)
{
	unsigned int	i;

	i = 0;
	pthread_join(system->monitor_thread, NULL);
	while (i < system->config.n_coders)
	{
		pthread_join(system->coders[i].thread, NULL);
		i++;
	}
	cleanup_system(system);
}
