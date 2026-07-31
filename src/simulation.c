/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: falamlih <falamlih@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/22 19:00:51 by falamlih          #+#    #+#             */
/*   Updated: 2026/07/31 00:30:28 by falamlih         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "headers.h"

void	*simulation(void *arg)
{
	t_coder	*coder;

	coder = (t_coder *)arg;
	while (!coder->system->stop)
	{
		request_scheduler(&coder->system->schedule, coder);
		take_dongles(coder);
		compiling(coder);
		relase_dongles(coder);
		scheduler_release(&coder->system->schedule);
		debugging(coder);
		refactoring(coder);
	}
	return (NULL);
}
