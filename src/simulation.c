/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: falamlih <falamlih@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/22 19:00:51 by falamlih          #+#    #+#             */
/*   Updated: 2026/08/04 06:34:33 by falamlih         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "headers.h"

unsigned int	coder_compiles(t_coder *coder)
{
	unsigned int	count;

	pthread_mutex_lock(&coder->mutex_coder);
	count = coder->compile_count;
	pthread_mutex_unlock(&coder->mutex_coder);
	return (count);
}

bool	all_coders_compile(t_system *system)
{
	unsigned int	i;

	i = 0;
	while (i < system->config.n_coders)
	{
		if (coder_compiles(&system->coders[i]) < system->config.compiles_required)
			return (false);
		i++;
	}
	return (true);
}
void	*simulation(void *arg)
{
	t_coder	*coder;

	coder = (t_coder *)arg;
	while (!system_is_stopped(coder->system)
		&& !all_coders_compile(coder->system))
	{
		if (system_is_stopped(coder->system))
			break ;
		take_dongles(coder);
		if (system_is_stopped(coder->system))
		{
			relase_dongles(coder);
			break ;
		}
		compiling(coder);
		if (system_is_stopped(coder->system))
		{
			break ;
		}
		if (system_is_stopped(coder->system))
			break ;
		debugging(coder);
		if (system_is_stopped(coder->system))
			break ;
		refactoring(coder);
	}
	return (NULL);
}
