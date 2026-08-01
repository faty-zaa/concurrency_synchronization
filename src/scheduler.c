/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scheduler.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: falamlih <falamlih@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/28 17:17:58 by falamlih          #+#    #+#             */
/*   Updated: 2026/08/01 05:55:38 by falamlih         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "headers.h"

void	scheduler_init(t_scheduler *scheduler, int capacity, char *algo)
{
	heap_init(&scheduler->edf, capacity);
	queue_init(&scheduler->fifo, capacity);
	scheduler->current = NULL;
	scheduler->algo = algo;
	pthread_mutex_init(&scheduler->mutex, NULL);
	if (pthread_mutex_init(&scheduler->mutex, NULL) != 0)
	{
		printf("mutex of scheduler fails\n");
		// SHOULD FREE CODERS, FREE DONGLES, DESTROY MUTEXES OF CODERS, DONLES,
		// system and destroy the heap and the queue
		return ;
	}
	pthread_cond_init(&scheduler->cond, NULL);
	if (pthread_cond_init(&scheduler->cond, NULL) != 0)
	{
		printf("cond_wait_init fails\n");
		// SHOULD FREE CODERS, FREE DONGLES, DESTROY MUTEXES OF CODERS, DONLES,
		// system and destroy the heap and the queue and scheduler init mutex
		return ;
	}
}

void	request_scheduler(t_scheduler *scheduler, t_coder *coder)
{
	pthread_mutex_lock(&scheduler->mutex);
	if (strcmp(scheduler->algo, "fifo") == 0)
		fifo_enqueue(&scheduler->fifo, coder);
	else if (strcmp(scheduler->algo, "edf") == 0)
		heap_insert(&scheduler->edf, coder);
	if (scheduler->current == NULL)
	{
		scheduler->current = scheduler_next(scheduler);
		pthread_cond_broadcast(&scheduler->cond);
	}
	while (scheduler->current != coder && !system_is_stopped(coder->system))
		pthread_cond_wait(&scheduler->cond, &scheduler->mutex);
	pthread_mutex_unlock(&scheduler->mutex);
}

t_coder	*scheduler_next(t_scheduler *scheduler)
{
	if (strcmp(scheduler->algo, "fifo") == 0)
		return (fifo_deque(&scheduler->fifo));
	else if (strcmp(scheduler->algo, "edf") == 0)
		return (heap_pop(&scheduler->edf));
	return (NULL);
}

void	scheduler_release(t_scheduler *scheduler)
{
	pthread_mutex_lock(&scheduler->mutex);
	scheduler->current = scheduler_next(scheduler);
	pthread_cond_broadcast(&scheduler->cond);
	pthread_mutex_unlock(&scheduler->mutex);
}

void	scheduler_destroy(t_scheduler *scheduler)
{
	pthread_mutex_destroy(&scheduler->mutex);
	pthread_cond_destroy(&scheduler->cond);
	free(scheduler->fifo.array);
	heap_destroy(&scheduler->edf);
}
