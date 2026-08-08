/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_system_help.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: falamlih <falamlih@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/07 23:27:44 by falamlih          #+#    #+#             */
/*   Updated: 2026/08/07 23:29:32 by falamlih         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "headers.h"

bool	alloc_system(t_system *system)
{
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
	return (true);
}

bool	init_dongle_queue(t_system *system, t_dongle *dongle)
{
	if (strcmp(dongle->algo, "edf") == 0)
	{
		if (!heap_init(&dongle->edf, system->config.n_coders))
		{
			printf("heap init fails\n");
			return (cleanup_system(system), false);
		}
	}
	else if (strcmp(dongle->algo, "fifo") == 0)
	{
		if (!queue_init(&dongle->fifo, system->config.n_coders))
		{
			printf("queue init fails\n");
			return (cleanup_system(system), false);
		}
	}
	return (true);
}

bool	init_one_dongle(t_system *system, unsigned int i)
{
	t_dongle	*dongle;

	dongle = &system->dongles[i];
	dongle->id = i;
	if (pthread_mutex_init(&dongle->mutex_dongle, NULL) != 0)
	{
		printf("mutex init of dongles fails\n");
		return (cleanup_system(system), false);
	}
	dongle->mutex_dongle_initialized = true;
	if (pthread_cond_init(&dongle->cond_dongle, NULL) != 0)
	{
		printf("cond init of dongles fails\n");
		return (cleanup_system(system), false);
	}
	dongle->cond_dongle_initialized = true;
	dongle->algo = system->config.scheduler;
	dongle->current = NULL;
	dongle->state = false;
	dongle->released_time = 0;
	return (init_dongle_queue(system, dongle));
}

bool	init_dongles(t_system *system)
{
	unsigned int	i;

	i = 0;
	while (i < system->config.n_coders)
	{
		if (!init_one_dongle(system, i))
			return (false);
		i++;
	}
	return (true);
}
