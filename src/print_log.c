/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_log.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: falamlih <falamlih@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/22 19:00:43 by falamlih          #+#    #+#             */
/*   Updated: 2026/07/25 19:05:40 by falamlih         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "headers.h"

void	take_dongles(t_coder *coder)
{
	printf("%ld %d has taken a dongle\n", coder->last_compile, coder->coder_id);
	// pthread_mutex_lock(&coder->left->mutex_dongle);
	printf("%ld %d has taken a dongle\n", coder->last_compile, coder->coder_id);
	// pthread_mutex_lock(&coder->right->mutex_dongle);
}

void	relase_dongles(t_coder *coder)
{
	pthread_mutex_unlock(&coder->left->mutex_dongle);
	pthread_mutex_unlock(&coder->right->mutex_dongle);
}

void	compiling(t_coder *coder)
{
	printf("%ld %d is compiling\n", coder->last_compile, coder->coder_id);
	usleep(coder->system->config.t_compile * 1000);
}

void	refactoring(t_coder *coder)
{
	printf("%ld %d is refactoring\n", coder->last_compile, coder->coder_id);
	usleep(coder->system->config.t_refactor * 1000);
}

void	debugging(t_coder *coder)
{
	printf("%ld %d is debugging\n", coder->last_compile, coder->coder_id);
	usleep(coder->system->config.t_debug * 1000);
}

void	burnout(t_coder *coder)
{
	printf("%ld %d burned out\n", coder->last_compile, coder->coder_id);
	usleep(coder->system->config.t_burnout * 1000);
}
