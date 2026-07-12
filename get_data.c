/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_data.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: falamlih <falamlih@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/12 14:52:31 by falamlih          #+#    #+#             */
/*   Updated: 2026/07/12 16:16:40 by falamlih         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "headers.h"

t_data	ft_get_data(char **arv)
{
	t_data	data;

	data.n_coders = ft_atoi(arv[1]);
	data.t_burnout = ft_atoi(arv[2]);
	data.t_compile = ft_atoi(arv[3]);
	data.t_debug = ft_atoi(arv[4]);
	data.t_refactor = ft_atoi(arv[5]);
	data.n_required = ft_atoi(arv[6]);
	data.d_cooldown = ft_atoi(arv[7]);
    data.scheduler = arv[8];
    
    return (data);
}
