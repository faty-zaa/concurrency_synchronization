/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_logs_help.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: falamlih <falamlih@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/07 23:30:53 by falamlih          #+#    #+#             */
/*   Updated: 2026/08/07 23:33:44 by falamlih         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "headers.h"

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

void	logs(t_coder *coder)
{
	log_print(coder, "has taken a dongle");
	log_print(coder, "has taken a dongle");
}
