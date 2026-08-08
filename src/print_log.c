/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_log.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: falamlih <falamlih@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/22 19:00:43 by falamlih          #+#    #+#             */
/*   Updated: 2026/08/08 23:08:29 by falamlih         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "headers.h"

bool	cooldown_is_done(t_dongle *dongle, t_system *system)
{
	if (dongle->released_time == 0)
		return (true);
	return (get_time_ms()
		- dongle->released_time >= (long)system->config.dongle_cooldown);
}

void	take_dongle(t_dongle *dongle, t_coder *coder, bool *waiting)
{
	pthread_mutex_lock(&dongle->mutex_dongle);
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
		if (dongle->current == NULL && cooldown_is_done(dongle, coder->system))
		{
			if (strcmp(coder->system->scheduler, "fifo") == 0)
				dongle->current = fifo_deque(&dongle->fifo);
			else
				dongle->current = heap_pop(&dongle->edf, 0, coder, 0);
		}
	}
	*waiting = false;
	if (dongle->current != coder)
	{
		pthread_cond_broadcast(&dongle->cond_dongle);
		pthread_mutex_unlock(&dongle->mutex_dongle);
	}
}

void	release_dongle(t_dongle *dongle, unsigned int rls)
{
	dongle->current = NULL;
	if (rls)
		dongle->released_time = rls;
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
		return (release_dongle(first, 0), false);
	}
	take_dongle(second, coder, &coder->waiting_right);
	if (second->current != coder)
		return (release_dongle(first, 0), false);
	logs(coder);
	return (true);
}

void	compiling(t_coder *coder)
{
	unsigned int	rls;

	pthread_mutex_lock(&coder->mutex_coder);
	coder->deadline = get_time_ms() - coder->system->starting_time
		+ coder->system->config.t_burnout;
	pthread_mutex_unlock(&coder->mutex_coder);
	log_print(coder, "is compiling");
	ft_sleep(get_time_ms() + coder->system->config.t_compile, coder);
	rls = get_time_ms();
	release_dongle(coder->left, rls);
	release_dongle(coder->right, rls);
	pthread_mutex_lock(&coder->mutex_coder);
	coder->compile_count++;
	pthread_mutex_unlock(&coder->mutex_coder);
}
