/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   creat_threads.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: falamlih <falamlih@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/22 19:01:01 by falamlih          #+#    #+#             */
/*   Updated: 2026/08/07 23:30:19 by falamlih         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "headers.h"

bool	creat_coders(t_system *system, unsigned int i)
{
	unsigned int	j;

	i = 0;
	while (i < system->config.n_coders)
	{
		if (pthread_create(&system->coders[i].thread, NULL, simulation,
				&system->coders[i]) != 0)
		{
			printf("creating coder thread %d fails\n", i);
			system_stop(system);
			j = 0;
			while (j < i)
			{
				if (system->coders[j].thread_created)
				{
					pthread_join(system->coders[j].thread, NULL);
					system->coders[j].thread_created = false;
				}
				j++;
			}
			return (false);
		}
		i++;
	}
	return (true);
}
