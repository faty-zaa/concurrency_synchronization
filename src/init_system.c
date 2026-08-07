/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_system.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: falamlih <falamlih@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/22 19:00:17 by falamlih          #+#    #+#             */
/*   Updated: 2026/08/07 02:45:46 by falamlih         ###   ########.fr       */
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

bool	init_system(t_system *system, t_config *config)
{
	unsigned int	i;

	system->config = *config;
	i = 0;
	system->coders = malloc(sizeof(t_coder) * system->config.n_coders);
	if (!system->coders)
	{
		printf("malloc fails in coders\n");
		return (false);
	}
	system->dongles = malloc(sizeof(t_dongle) * system->config.n_coders);
	if (!system->dongles)
	{
		printf("malloc fails in dongles\n");
		cleanup_system(system);
		return (false);
	}
	while (i < system->config.n_coders)
	{
		system->dongles[i].id = i;
		if (pthread_mutex_init(&system->dongles[i].mutex_dongle, NULL) != 0)
		{
			printf("mutex init of dongles fails\n");
			cleanup_system(system);
			return (false);
		}
		system->dongles[i].mutex_dongle_initialized = true;
		if (pthread_cond_init(&system->dongles[i].cond_dongle, NULL) != 0)
		{
			printf("cond init of dongles fails\n");
			cleanup_system(system);
			return (false);
		}
		system->dongles[i].cond_dongle_initialized = true;
		system->dongles[i].algo = system->config.scheduler;
		system->dongles[i].current = NULL;
		system->dongles[i].state = false;
		system->dongles[i].released_time = 0;
		if (strcmp(system->dongles[i].algo, "edf") == 0)
		{
			if (!heap_init(&system->dongles[i].edf, system->config.n_coders))
			{
				printf("heap init fails\n");
				cleanup_system(system);
				return (false);
			}
		}
		else if (strcmp(system->dongles[i].algo, "fifo") == 0)
		{
			if (!queue_init(&system->dongles[i].fifo, system->config.n_coders))
			{
				printf("queue init fails\n");
				cleanup_system(system);
				return (false);
			}
		}
		i++;
	}
	if (pthread_mutex_init(&system->print_mutex, NULL) != 0
		|| pthread_mutex_init(&system->stop_mutex, NULL) != 0)
	{
		printf("mutex init fails\n");
		cleanup_system(system);
		return (false);
	}
	system->print_mutex_initialized = true;
	system->stop_mutex_initialized = true;
	system->starting_time = get_time_ms();
	i = 0;
	while (i < system->config.n_coders)
	{
		system->coders[i].coder_id = i + 1;
		system->coders[i].compile_count = 0;
		system->coders[i].last_compile = system->starting_time;
		system->coders[i].system = system;
		system->coders[i].deadline = system->config.t_burnout;
		system->coders[i].waiting_left = false;
		system->coders[i].waiting_right = false;
		system->coders[i].left = &system->dongles[i];
		system->coders[i].thread_created = true;
		if (pthread_mutex_init(&system->coders[i].mutex_coder, NULL) != 0)
		{
			printf("mutex init of coder %d fails\n", i);
			cleanup_system(system);
			return (false);
		}
		system->coders[i].mutex_coder_initialized = true;
		if ((i + 1) == config->n_coders)
			system->coders[i].right = &system->dongles[0];
		else
			system->coders[i].right = &system->dongles[i + 1];
		i++;
	}
	system->scheduler = config->scheduler;
	system->stop = false;
	if (!creat_coders(system, 0))
	{
		cleanup_system(system);
		return (false);
	}
	if (pthread_create(&system->monitor_thread, NULL, monitor, system) != 0)
	{
		printf("monitor thread creation fails\n");
		system_stop(system);
		cleanup_system(system);
		return (false);
	}
	system->monitor_thread_created = true;
	return (true);
}
