/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: falamlih <falamlih@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/22 19:00:51 by falamlih          #+#    #+#             */
/*   Updated: 2026/07/25 19:04:35 by falamlih         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "headers.h"

void	*simulation(void *arg)
{
	t_coder	*coder;

	coder = (t_coder *)arg;
	
	take_dongles(coder);
	compiling(coder);
	refactoring(coder);
	debugging(coder);
	burnout(coder);
	return (NULL);
}
