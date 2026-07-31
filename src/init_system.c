/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_system.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: falamlih <falamlih@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/22 19:00:17 by falamlih          #+#    #+#             */
/*   Updated: 2026/07/31 01:13:05 by falamlih         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "headers.h"

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
		pthread_mutex_init(&system->dongles[i].mutex_dongle, NULL);
		i++;
	}
	pthread_mutex_init(&system->print_mutex, NULL);
	system->starting_time = get_time_ms();
	i = 0;
	while (i < system->config.n_coders)
	{
		system->coders[i].coder_id = i;
		system->coders[i].compile_count = 0;
		system->coders[i].last_compile = system->starting_time;
		system->coders[i].system = system;
		system->coders[i].deadline = 0;
		system->coders[i].state = 0;
		system->coders[i].left = &system->dongles[i];
		pthread_mutex_init(&system->coders[i].mutex_coder, NULL);
		if ((i + 1) == config->n_coders)
			system->coders[i].right = &system->dongles[0];
		else
			system->coders[i].right = &system->dongles[i + 1];
		i++;
	}
	system->scheduler = config->scheduler;
	system->stop = false;
	scheduler_init(&system->schedule, 15, config->scheduler);
	creat_coders(system);
	pthread_create(&system->monitor_thread, NULL,
			monitor, system);
}
