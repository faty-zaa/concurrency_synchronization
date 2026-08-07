/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   queue.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: falamlih <falamlih@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/29 02:09:31 by falamlih          #+#    #+#             */
/*   Updated: 2026/07/31 17:47:44 by falamlih         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "headers.h"

bool	queue_init(t_queue *queue, int capacity)
{
	queue->array = malloc(sizeof(t_coder *) * capacity);
	if (!queue->array)
		return (false);
	queue->size = 0;
	queue->capacity = capacity;
	return (true);
}

void	queue_destroy(t_queue *queue)
{
	if (!queue)
		return ;
	free(queue->array);
	queue->array = NULL;
	queue->size = 0;
	queue->capacity = 0;
}

void	fifo_enqueue(t_queue *queue, t_coder *coder)
{
	if (queue->size == queue->capacity)
		return ;
	queue->array[queue->size] = coder;
	queue->size++;
}

t_coder	*fifo_deque(t_queue *queue)
{
	t_coder			*coder;
	unsigned int	i;

	if (queue->size == 0)
		return (NULL);
	coder = queue->array[0];
	i = 0;
	while (i < queue->size - 1)
	{
		queue->array[i] = queue->array[i + 1];
		i++;
	}
	queue->size--;
	return (coder);
}
