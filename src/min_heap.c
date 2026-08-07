/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   min_heap.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: falamlih <falamlih@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/22 19:00:34 by falamlih          #+#    #+#             */
/*   Updated: 2026/08/07 03:08:53 by falamlih         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "headers.h"

bool	heap_init(t_heap *heap, int capacity)
{
	heap->array = malloc(sizeof(t_coder *) * capacity);
	if (!heap->array)
		return (false);
	heap->size = 0;
	heap->capacity = capacity;
	return (true);
}

void	heap_destroy(t_heap *heap)
{
	if (!heap)
		return ;
	free(heap->array);
	heap->array = NULL;
	heap->size = 0;
	heap->capacity = 0;
}

void	heap_insert(t_heap *heap, t_coder *coder)
{
	int		i;
	int		j;
	t_coder	*swap;

	i = heap->size;
	heap->array[heap->size] = coder;
	while (i > 0)
	{
		j = (i - 1) / 2;
		if (deadline(heap->array[j]) > deadline(heap->array[i]))
		{
			swap = heap->array[j];
			heap->array[j] = heap->array[i];
			heap->array[i] = swap;
			i = j;
		}
		else
			break ;
	}
	heap->size += 1;
}

void	ft_swap(t_coder *a, t_coder *b)
{
	t_coder	swap;

	swap = *a;
	*a = *b;
	*b = swap;
}

t_coder	*heap_pop(t_heap *heap, int i, t_coder *coder, int small)
{
	unsigned int	left;
	unsigned int	right;

	if (heap->size == 0)
		return (NULL);
	coder = heap->array[0];
	heap->size--;
	heap->array[0] = heap->array[heap->size];
	while (1)
	{
		small = i;
		left = 2 * i + 1;
		right = 2 * i + 2;
		if (left < heap->size
			&& deadline(heap->array[left]) < deadline(heap->array[small]))
			small = left;
		if (right < heap->size
			&& deadline(heap->array[right]) < deadline(heap->array[small]))
			small = right;
		if (small == i)
			break ;
		ft_swap(heap->array[i], heap->array[small]);
		i = small;
	}
	return (coder);
}
