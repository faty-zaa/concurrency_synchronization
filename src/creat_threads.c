/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   creat_threads.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: falamlih <falamlih@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/22 19:01:01 by falamlih          #+#    #+#             */
/*   Updated: 2026/07/25 19:06:16 by falamlih         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "headers.h"

void	creat_coders(t_system *system)
{
	unsigned int i;

	i = 0;
	while (i < system->config.n_coders)
	{
		pthread_create(&system->coders[i].thread, NULL, simulation,
			&system->coders[i]);
		i++;
	}
}
