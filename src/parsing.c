/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: falamlih <falamlih@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/12 10:41:42 by falamlih          #+#    #+#             */
/*   Updated: 2026/07/23 16:22:08 by falamlih         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "headers.h"

int	ft_parsing(int arc, char **arv)
{
	int	count_args;

	if (arc < 9 || arc > 9)
	{
		printf("Error: requiered 8 args, 7 numbers and one string");
		return (0);
	}
	count_args = 1;
	while (count_args < arc - 1)
	{
		if (!ft_check_args(arv, count_args))
			return (0);
		count_args++;
	}
	if (!ft_isalpha(arv[count_args]))
	{
		printf("Error: Last argument should be string");
		return (0);
	}
	else if ((strcmp("fifo", ft_tolower(arv[count_args])) != 0)
		&& (strcmp("edf", ft_tolower(arv[count_args])) != 0))
	{
		printf("Error: The value must be exactly one of: fifo or edf");
		return (0);
	}
	return (1);
}
