/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: falamlih <falamlih@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/12 10:42:01 by falamlih          #+#    #+#             */
/*   Updated: 2026/07/19 17:58:37 by falamlih         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "headers.h"
#include <unistd.h>

void	myturn(void)
{
	while (1)
	{
		printf("My trun\n");
		sleep(1);
	}
}
void	*yturn(void *)
{
	while (1)
	{
		printf("y trun\n");
		sleep(1);
	}
	return (NULL);
}
int	main(void)
{
	pthread_t	new;

	pthread_create(&new, NULL, yturn, NULL);
	myturn();
	// pthread_create(&new, NULL, myturn, NULL);
}

// #include "headers.h"

// int main(int arc, char **arv)
// {
// 	if (!ft_parsing(arc, arv))
// 		return (0);
// 	t_data data = ft_get_data(arv);
// 	printf("%d", data.d_cooldown);
// }