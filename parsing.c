/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: falamlih <falamlih@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/12 10:41:42 by falamlih          #+#    #+#             */
/*   Updated: 2026/07/12 16:55:52 by falamlih         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "headers.h"
// »»-----► Number of lines: 16
size_t	ft_isalpha1(char *c)
{
	size_t	i;
	size_t	n;

	i = 0;
	n = 0;
	while (i < strlen(c))
	{
		if ((c[i] >= 97 && c[i] <= 122) || (c[i] >= 65 && c[i] <= 90))
			i++;
		else
		{
			n++;
			i++;
		}
	}
	return (n);
}
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
// »»-----► Number of lines: 17
long	ft_atoi(const char *nptr)
{
	int		i;
	long	nj;

	i = 0;
	while ((nptr[i] >= 9 && nptr[i] <= 13) || nptr[i] == ' ')
		i++;
	nj = 0;
	while (nptr[i] >= '0' && nptr[i] <= '9')
	{
		if (nj >= 2147483647 || nj < 0)
			return (-1);
		nj = nj * 10 + (nptr[i] - '0');
		i++;
	}
	if (nj >= 2147483647 || nj < 0 || nptr[i] != '\0')
		return (-1);
	return (nj);
}

int	ft_check_args(char **arv, int count)
{
	long	nb;

	if (ft_isalpha1(arv[count]) != strlen(arv[count]))
	{
		printf("Error: first 7 arguments should be numbers");
		return (0);
	}
	nb = ft_atoi(arv[count]);
	if (nb == -1)
	{
		printf("Error: all input numbers should be valid positif integers");
		return (0);
	}
	else if (nb >= 2147483647)
	{
		printf("Error: Input numbers should be integers(less than 2147483647)");
		return (0);
	}
	return (1);
}

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
