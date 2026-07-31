/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_time.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: falamlih <falamlih@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/22 19:00:25 by falamlih          #+#    #+#             */
/*   Updated: 2026/07/31 01:25:55 by falamlih         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "headers.h"

long	get_time_ms(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return (tv.tv_sec * 1000L + tv.tv_usec / 1000);
}

long	deadline(t_coder *coder)
{
	long	deadline;

	deadline = coder->last_compile + coder->system->config.t_burnout;
	return (deadline);
}

long	get_time(t_system *system)
{
	return (get_time_ms() - system->starting_time);
}

long	count_burnout(long last)
{
	return (get_time_ms() - last);
}