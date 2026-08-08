/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   join_threads.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: falamlih <falamlih@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/23 17:00:38 by falamlih          #+#    #+#             */
/*   Updated: 2026/08/07 23:32:09 by falamlih         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "headers.h"

void	clean_coders(t_system *system)
{
	unsigned int	i;

	i = 0;
	while (i < system->config.n_coders)
	{
		if (system->coders[i].mutex_coder_initialized)
			pthread_mutex_destroy(&system->coders[i].mutex_coder);
		i++;
	}
	free(system->coders);
	system->coders = NULL;
}

void	clean_dongles(t_system *system)
{
	unsigned int	i;

	i = 0;
	while (i < system->config.n_coders)
	{
		if (system->dongles[i].mutex_dongle_initialized)
			pthread_mutex_destroy(&system->dongles[i].mutex_dongle);
		if (system->dongles[i].cond_dongle_initialized)
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

void	cleanup_system(t_system *system)
{
	if (!system)
		return ;
	if (system->coders)
		clean_coders(system);
	if (system->dongles)
		clean_dongles(system);
	if (system->print_mutex_initialized)
		pthread_mutex_destroy(&system->print_mutex);
	if (system->stop_mutex_initialized)
		pthread_mutex_destroy(&system->stop_mutex);
}

void	join_threads(t_system *system)
{
	unsigned int	i;

	i = 0;
	if (system->monitor_thread_created)
		pthread_join(system->monitor_thread, NULL);
	while (i < system->config.n_coders)
	{
		if (system->coders[i].thread_created)
			pthread_join(system->coders[i].thread, NULL);
		i++;
	}
	cleanup_system(system);
}
