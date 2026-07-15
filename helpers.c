/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helpers.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: falamlih <falamlih@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/13 18:45:23 by falamlih          #+#    #+#             */
/*   Updated: 2026/07/14 22:20:22 by falamlih         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "headers.h"

size_t	ft_isalpha_num(char *c)
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

	if (ft_isalpha_num(arv[count]) != strlen(arv[count]))
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
