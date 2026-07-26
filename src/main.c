/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: falamlih <falamlih@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/12 10:42:01 by falamlih          #+#    #+#             */
/*   Updated: 2026/07/26 16:56:56 by falamlih         ###   ########.fr       */
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
	creat_coders(&system);
	join_threads(&system);
	return 0;
}
