/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_data.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: falamlih <falamlih@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/12 14:52:31 by falamlih          #+#    #+#             */
/*   Updated: 2026/08/07 06:50:14 by falamlih         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "headers.h"

t_config	ft_get_config(char **arv)
{
	t_config	data;

	data.n_coders = ft_atoi(arv[1]);
	data.t_burnout = ft_atoi(arv[2]);
	data.t_compile = ft_atoi(arv[3]);
	data.t_debug = ft_atoi(arv[4]);
	data.t_refactor = ft_atoi(arv[5]);
	data.compiles_required = ft_atoi(arv[6]);
	data.dongle_cooldown = ft_atoi(arv[7]);
	data.scheduler = arv[8];
	return (data);
}

void	refactoring(t_coder *coder)
{
	log_print(coder, "is refactoring");
	ft_sleep(get_time_ms() + coder->system->config.t_refactor, coder);
}

void	debugging(t_coder *coder)
{
	log_print(coder, "is debugging");
	ft_sleep(get_time_ms() + coder->system->config.t_debug, coder);
}

void	burnout(t_coder *coder)
{
	log_print(coder, "burned out");
}
