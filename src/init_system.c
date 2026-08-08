/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_system.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: falamlih <falamlih@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/22 19:00:17 by falamlih          #+#    #+#             */
/*   Updated: 2026/08/07 23:29:55 by falamlih         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "headers.h"

static bool	init_global_mutexes(t_system *system)
{
	if (pthread_mutex_init(&system->print_mutex, NULL) != 0
		|| pthread_mutex_init(&system->stop_mutex, NULL) != 0)
	{
		printf("mutex init fails\n");
		return (cleanup_system(system), false);
	}
	system->print_mutex_initialized = true;
	system->stop_mutex_initialized = true;
	return (true);
}

static bool	init_one_coder(t_system *system, unsigned int i)
{
	t_coder	*coder;

	coder = &system->coders[i];
	coder->coder_id = i + 1;
	coder->compile_count = 0;
	coder->last_compile = system->starting_time;
	coder->system = system;
	coder->deadline = system->config.t_burnout;
	coder->waiting_left = false;
	coder->waiting_right = false;
	coder->left = &system->dongles[i];
	coder->thread_created = true;
	if (pthread_mutex_init(&coder->mutex_coder, NULL) != 0)
	{
		printf("mutex init of coder %d fails\n", i);
		return (cleanup_system(system), false);
	}
	coder->mutex_coder_initialized = true;
	if ((i + 1) == system->config.n_coders)
		coder->right = &system->dongles[0];
	else
		coder->right = &system->dongles[i + 1];
	return (true);
}

static bool	init_coders(t_system *system)
{
	unsigned int	i;

	i = 0;
	while (i < system->config.n_coders)
	{
		if (!init_one_coder(system, i))
			return (false);
		i++;
	}
	return (true);
}

static bool	start_threads(t_system *system)
{
	if (!creat_coders(system, 0))
		return (cleanup_system(system), false);
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

bool	init_system(t_system *system, t_config *config)
{
	system->config = *config;
	if (!alloc_system(system))
		return (false);
	if (!init_dongles(system))
		return (false);
	if (!init_global_mutexes(system))
		return (false);
	system->starting_time = get_time_ms();
	if (!init_coders(system))
		return (false);
	system->scheduler = config->scheduler;
	system->stop = false;
	return (start_threads(system));
}
