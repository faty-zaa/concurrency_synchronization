/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_log.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: falamlih <falamlih@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/22 19:00:43 by falamlih          #+#    #+#             */
/*   Updated: 2026/07/31 01:22:21 by falamlih         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "headers.h"

void	log_print(t_coder *coder, const char *msg)
{
	pthread_mutex_lock(&coder->system->print_mutex);
	printf("%ld %d %s\n", get_time(coder->system), coder->coder_id, msg);
	pthread_mutex_unlock(&coder->system->print_mutex);
}

void	take_dongles(t_coder *coder)
{
	pthread_mutex_lock(&coder->left->mutex_dongle);
	log_print(coder, "has taken a dongle");
	pthread_mutex_lock(&coder->right->mutex_dongle);
	log_print(coder, "has taken a dongle");
}

void	relase_dongles(t_coder *coder)
{
	pthread_mutex_unlock(&coder->left->mutex_dongle);
	pthread_mutex_unlock(&coder->right->mutex_dongle);
}

void	compiling(t_coder *coder)
{
	log_print(coder, "is compiling");
	pthread_mutex_lock(&coder->mutex_coder);
	coder->last_compile = get_time_ms();
	pthread_mutex_unlock(&coder->mutex_coder);
	usleep(coder->system->config.t_compile * 1000);
	pthread_mutex_lock(&coder->mutex_coder);
	coder->compile_count++;
	pthread_mutex_unlock(&coder->mutex_coder);
}

void	refactoring(t_coder *coder)
{
	log_print(coder, "is refactoring");
	usleep(coder->system->config.t_refactor * 1000);
}

void	debugging(t_coder *coder)
{
	log_print(coder, "is debugging");
	usleep(coder->system->config.t_debug * 1000);
}

void	burnout(t_coder *coder)
{
	log_print(coder, "burned out");
}
