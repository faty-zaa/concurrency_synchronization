/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_log.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: falamlih <falamlih@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/22 19:00:43 by falamlih          #+#    #+#             */
/*   Updated: 2026/08/07 05:33:25 by falamlih         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "headers.h"

void	log_print(t_coder *coder, const char *msg)
{
	pthread_mutex_lock(&coder->system->print_mutex);
	printf("%ld %d %s\n", get_time(coder->system), coder->coder_id, msg);
	pthread_mutex_unlock(&coder->system->print_mutex);
}

void	ft_sleep(long ms, t_coder *coder)
{
	while (get_time_ms() < ms)
	{
		usleep(1000);
		if (system_is_stopped(coder->system))
			break ;
	}
}
bool	cooldown_is_done(t_dongle *dg, long col)
{
	bool	value;

	pthread_mutex_lock(&dg->mutex_dongle);
	value = (get_time_ms() > dg->released_time + col);
	if (dg->released_time == 0)
		value = true;
	pthread_mutex_unlock(&dg->mutex_dongle);
	return (value);
}
void	take_dongle(t_dongle *dongle, t_coder *coder, bool *waiting)
{
	pthread_mutex_lock(&dongle->mutex_dongle);
	// if (cooldown_is_done(dongle, coder->system->config.dongle_cooldown))
	// 	return (false);
	if (!*waiting)
	{
		if (strcmp(coder->system->scheduler, "fifo") == 0)
			fifo_enqueue(&dongle->fifo, coder);
		else
			heap_insert(&dongle->edf, coder);
		*waiting = true;
	}
	while (dongle->current != coder && !system_is_stopped(coder->system))
	{
		if (dongle->current == NULL)
		{
			if (strcmp(coder->system->scheduler, "fifo") == 0)
				dongle->current = fifo_deque(&dongle->fifo);
			else
				dongle->current = heap_pop(&dongle->edf, 0, coder, 0);
			pthread_cond_broadcast(&dongle->cond_dongle);
		}
		if (dongle->current != coder)
			pthread_cond_wait(&dongle->cond_dongle, &dongle->mutex_dongle);
	}
	*waiting = false;
	if (dongle->current != coder)
		pthread_mutex_unlock(&dongle->mutex_dongle);
	return ;
}
void	release_dongle(t_dongle *dongle, t_system *system)
{
	dongle->current = NULL;
	dongle->released_time = get_time(system);
	pthread_cond_broadcast(&dongle->cond_dongle);
	pthread_mutex_unlock(&dongle->mutex_dongle);
}

bool	take_dongles(t_coder *coder)
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
	take_dongle(first, coder, &coder->waiting_left);
	if (first->current != coder)
		return (false);
	if (first == second)
	{
		log_print(coder, "has taken a dongle");
		while (!system_is_stopped(coder->system))
			pthread_cond_wait(&first->cond_dongle, &first->mutex_dongle);
		release_dongle(first, coder->system);
		return (false);
	}
	take_dongle(second, coder, &coder->waiting_right);
	if (second->current != coder)
	{
		release_dongle(first, coder->system);
		return (false);
	}
	log_print(coder, "has taken a dongle");
	log_print(coder, "has taken a dongle");
	return (true);
}

void	compiling(t_coder *coder)
{
	pthread_mutex_lock(&coder->mutex_coder);
	coder->deadline = get_time_ms() - coder->system->starting_time
		+ coder->system->config.t_burnout;
	pthread_mutex_unlock(&coder->mutex_coder);
	log_print(coder, "is compiling");
	ft_sleep(get_time_ms() + coder->system->config.t_compile, coder);
	release_dongle(coder->left, coder->system);
	release_dongle(coder->right, coder->system);
	pthread_mutex_lock(&coder->mutex_coder);
	coder->compile_count++;
	pthread_mutex_unlock(&coder->mutex_coder);
}

void	refactoring(t_coder *coder)
{
	log_print(coder, "is refactoring");
	ft_sleep(get_time_ms() + coder->system->config.t_refactor, coder);
}

void	debugging(t_coder *coder)
{
	log_print(coder, "is debugging");
	ft_sleep(get_time_ms() + coder->system->config.t_debug, coder);
}

void	burnout(t_coder *coder)
{
	log_print(coder, "burned out");
}
void	*simulation(void *args)
{
	t_coder	*coder;

	coder = (t_coder *)args;
	while (!system_is_stopped(coder->system))
	{
		if (!take_dongles(coder))
			break ;
		compiling(coder);
		if (system_is_stopped(coder->system))
			break ;
		debugging(coder);
		if (system_is_stopped(coder->system))
			break ;
		refactoring(coder);
	}
	return (NULL);
}
