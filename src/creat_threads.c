/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   creat_threads.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: falamlih <falamlih@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/22 19:01:01 by falamlih          #+#    #+#             */
/*   Updated: 2026/08/01 01:44:27 by falamlih         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "headers.h"

void	creat_coders(t_system *system)
{
	unsigned int	i;
	int				check;

	i = 0;
	while (i < system->config.n_coders)
	{
		check = pthread_create(&system->coders[i].thread, NULL, simulation,
				&system->coders[i]);
		if (check != 0)
		{
			printf("creating coder thread %d fails", i);
			// destroy the threads created before he one fails
			// SHOULD FREE CODERS, FREE DONGLES, DESTROY MUTEXES OF CODERS,DONLES,
			// system and destroy the heap and the queue and scheduler init mutex and cond init
			return;
		}
		i++;
	}
}
