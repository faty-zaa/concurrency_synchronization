/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_log.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: falamlih <falamlih@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/22 19:00:43 by falamlih          #+#    #+#             */
/*   Updated: 2026/08/03 06:12:17 by falamlih         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "headers.h"

void	log_print(t_coder *coder, const char *msg)
{
	pthread_mutex_lock(&coder->system->print_mutex);
	printf("%ld %d %s\n", get_time(coder->system), coder->coder_id, msg);
	pthread_mutex_unlock(&coder->system->print_mutex);
}

void	take_dongle(t_dongle *dongle, t_coder *coder)
{
	pthread_mutex_lock(&dongle->mutex_dongle);
	if (coder_compiles(coder) >= coder->system->config.compiles_required)
		return ;
	if (strcmp(coder->system->scheduler, "fifo") == 0)
		fifo_enqueue(&dongle->fifo, coder);
	else if (strcmp(coder->system->scheduler, "edf") == 0)
		heap_insert(&dongle->edf, coder);
	if (dongle->current == NULL)
	{
		if (strcmp(coder->system->scheduler, "fifo") == 0)
			dongle->current = fifo_deque(&dongle->fifo);
		else
			dongle->current = heap_pop(&dongle->edf);
		pthread_cond_broadcast(&dongle->cond_dongle);
	}
	while (dongle->current != coder)
		pthread_cond_wait(&dongle->cond_dongle, &dongle->mutex_dongle);
	log_print(coder, "has taken a dongle");
}

void	relase_dongle(t_dongle *dongle)
{
	if (strcmp(dongle->algo, "fifo") == 0)
		dongle->current = fifo_deque(&dongle->fifo);
	else if (strcmp(dongle->algo, "edf") == 0)
		dongle->current = heap_pop(&dongle->edf);
	pthread_cond_broadcast(&dongle->cond_dongle);
	pthread_mutex_unlock(&dongle->mutex_dongle);
}

void	take_dongles(t_coder *coder)
{
	t_dongle	*first;
	t_dongle	*second;

	first = coder->left;
	second = coder->right;
	if (first->id > second->id)
	{
		first = coder->right;
		second = coder->left;
	}
	take_dongle(first, coder);
	take_dongle(second, coder);
}
void	relase_dongles(t_coder *coder)
{
	t_dongle	*first;
	t_dongle	*second;

	first = coder->left;
	second = coder->right;
	if (first->id > second->id)
	{
		first = coder->right;
		second = coder->left;
	}
	relase_dongle(first);
	relase_dongle(second);
}
void	compiling(t_coder *coder)
{
	log_print(coder, "is compiling");
	pthread_mutex_lock(&coder->mutex_coder);
	coder->last_compile = get_time_ms();
	coder->deadline = coder->last_compile + coder->system->config.t_burnout;
	pthread_mutex_unlock(&coder->mutex_coder);
	usleep(coder->system->config.t_compile * 1000);
	relase_dongles(coder);
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
