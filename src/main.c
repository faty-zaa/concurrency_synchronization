/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: falamlih <falamlih@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/12 10:42:01 by falamlih          #+#    #+#             */
/*   Updated: 2026/07/30 23:40:17 by falamlih         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "headers.h"

int	main(int arc, char **arv)
{
	if (!ft_parsing(arc, arv))
		return (0);
	t_system system;
	t_config config = ft_get_config(arv);
	init_system(&system, &config);
	join_threads(&system);
	return 0;
}
