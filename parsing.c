/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: falamlih <falamlih@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/12 10:41:42 by falamlih          #+#    #+#             */
/*   Updated: 2026/07/12 12:51:36 by falamlih         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "headers.h"

// int	n_coders;
// int	t_burnout;
// int	t_compile;
// int	t_debug;
// int	t_refactor;
// int	n_required;
// int	d_cooldown;
// char *scheduler;
// »»-----► Number of lines: 11
int	ft_isalpha(char *c)
{
	size_t	i;

	i = 0;
	while (i < strlen(c))
	{
		if ((c[i] >= 97 && c[i] <= 122) || (c[i] >= 65 && c[i] <= 90))
			i++;
		else
			return (0);
	}
	return (1);
}
// »»-----► Number of lines: 10
char	*ft_tolower(char *c)
{
	size_t	i;

	i = 0;
	while (i < strlen(c))
	{
		if (c[i] >= 65 && c[i] <= 90)
			c[i] = c[i] + 32;
		i++;
	}
	return (c);
}
// »»-----► Number of lines: 18
int	ft_check_args(char **arv, int count)
{
	long	nb;

	if (ft_isalpha(arv[count]))
	{
		printf("Error: first 7 arguments should be numbers");
		return (0);
	}
	nb = (long)atoi(arv[count]);
	if (nb < 0)
	{
		printf("Error: all input numbers should be greater than 0");
		return (0);
	}
	else if (nb >= 2147483647)
	{
		printf("Error: all input numbers should be inside int range (less than 2147483647)");
		return (0);
	}
	return (1);
}
// »»-----► Number of lines: 25
void	ft_parsing(int arc, char **arv)
{
	int	count_args;

	if (arc < 9 || arc > 9)
	{
		printf("Error: requiered 8 args, 7 numbers and one string");
		return ;
	}
	count_args = 1;
	while (count_args < arc - 1)
	{
		if (!ft_check_args(arv, count_args))
			return ;
		count_args++;
	}
	if (!ft_isalpha(arv[count_args]))
	{
		printf("Error: Last argument should be string");
		return ;
	}
	else if ((strcmp("fifo", ft_tolower(arv[count_args])) != 0)
		&& (strcmp("edf", ft_tolower(arv[count_args])) != 0))
	{
		printf("Error: The value must be exactly one of: fifo or edf");
		return ;
	}
}
