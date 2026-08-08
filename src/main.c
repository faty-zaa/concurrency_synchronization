/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: falamlih <falamlih@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/12 10:42:01 by falamlih          #+#    #+#             */
/*   Updated: 2026/08/08 23:06:36 by falamlih         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "headers.h"

int	main(int arc, char **arv)
{
	t_system	system;
	t_config	config;

	if (!ft_parsing(arc, arv))
		return (0);
	config = ft_get_config(arv);
	if (config.n_coders > 1000)
	{
		printf("Only less than 1k coder allowed");
		return (0);
	}
	if (!init_system(&system, &config))
		return (0);
	join_threads(&system);
	return (0);
}
