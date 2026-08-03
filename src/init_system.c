/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_system.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: falamlih <falamlih@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/22 19:00:17 by falamlih          #+#    #+#             */
/*   Updated: 2026/08/03 06:34:49 by falamlih         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "headers.h"

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

void	init_system(t_system *system, t_config *config)
{
	unsigned int	i;

	system->config = *config;
	i = 0;
	system->coders = malloc(sizeof(t_coder) * system->config.n_coders);
	if (!system->coders)
	{
		printf("malloc fails in coders");
		return ;
	}
	system->dongles = malloc(sizeof(t_dongle) * system->config.n_coders);
	if (!system->dongles)
	{
		free(system->coders);
		printf("malloc fails in dongles");
		return ;
	}
	while (i < system->config.n_coders)
	{
		system->dongles[i].id = i;
		if (pthread_mutex_init(&system->dongles[i].mutex_dongle, NULL) != 0)
		{
			printf("mutex init of dongles fails\n");
			return ;
		}
		if (pthread_cond_init(&system->dongles[i].cond_dongle, NULL) != 0)
		{
			printf("cond init of dongles fails\n");
			return ;
		}
		system->dongles[i].released_time = 0;
		system->dongles[i].algo = system->config.scheduler;
		system->dongles[i].current = NULL;
		system->dongles[i].state = false;
		if (strcmp(system->dongles[i].algo, "edf") == 0)
			heap_init(&system->dongles[i].edf, 2);
		else if (strcmp(system->dongles[i].algo, "fifo") == 0)
			queue_init(&system->dongles[i].fifo, 2);
		i++;
	}
	if (pthread_mutex_init(&system->print_mutex, NULL) != 0
		|| pthread_mutex_init(&system->stop_mutex, NULL) != 0)
	{
		printf("mutex init fails\n");
		return ;
	}
	system->starting_time = get_time_ms();
	i = 0;
	while (i < system->config.n_coders)
	{
		system->coders[i].coder_id = i + 1;
		system->coders[i].compile_count = 0;
		system->coders[i].last_compile = system->starting_time;
		system->coders[i].system = system;
		system->coders[i].deadline = 0;
		system->coders[i].state = 0;
		system->coders[i].waiting = false;
		system->coders[i].left = &system->dongles[i];
		if (pthread_mutex_init(&system->coders[i].mutex_coder, NULL) != 0)
		{
			printf("mutex init of coder %d fails\n", i);
			return ;
		}
		if ((i + 1) == config->n_coders)
			system->coders[i].right = &system->dongles[0];
		else
			system->coders[i].right = &system->dongles[i + 1];
		i++;
	}
	system->scheduler = config->scheduler;
	system->stop = false;
	// should check if fails inside by making somthing returned
	creat_coders(system);
	// should check if fails inside by making somthing returned
	pthread_create(&system->monitor_thread, NULL, monitor, system);
}
