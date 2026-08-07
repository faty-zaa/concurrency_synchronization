/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_time.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: falamlih <falamlih@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/22 19:00:25 by falamlih          #+#    #+#             */
/*   Updated: 2026/08/07 02:13:54 by falamlih         ###   ########.fr       */
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
	return (coder->deadline);
}

long	get_time(t_system *system)
{
	return (get_time_ms() - system->starting_time);
}

long	count_burnout(long last)
{
	return (get_time_ms() - last);
}
