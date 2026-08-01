/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: falamlih <falamlih@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/22 19:00:51 by falamlih          #+#    #+#             */
/*   Updated: 2026/08/01 05:50:07 by falamlih         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "headers.h"

void	*simulation(void *arg)
{
	t_coder *coder;

	coder = (t_coder *)arg;
	while (!system_is_stopped(coder->system))
	{
		request_scheduler(&coder->system->schedule, coder);
		if (system_is_stopped(coder->system))
			break ;
		take_dongles(coder);
		if (system_is_stopped(coder->system))
		{
			relase_dongles(coder);
			scheduler_release(&coder->system->schedule);
			break ;
		}
		compiling(coder);
		if (system_is_stopped(coder->system))
		{
			relase_dongles(coder);
			scheduler_release(&coder->system->schedule);
			break ;
		}
		relase_dongles(coder);
		scheduler_release(&coder->system->schedule);
		if (system_is_stopped(coder->system))
			break ;
		debugging(coder);
		if (system_is_stopped(coder->system))
			break ;
		refactoring(coder);
	}
	return (NULL);
}
