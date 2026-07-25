/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   join_threads.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: falamlih <falamlih@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/23 17:00:38 by falamlih          #+#    #+#             */
/*   Updated: 2026/07/25 01:31:29 by falamlih         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "headers.h"

void	join_threads(t_system *system)
{
    unsigned int  i;

	i = 0;
	while (i < system->config.n_coders)
	{
		pthread_join(system->coders[i].thread, NULL);
		i++;
	}
}
