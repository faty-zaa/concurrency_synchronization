/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: falamlih <falamlih@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/12 10:42:01 by falamlih          #+#    #+#             */
/*   Updated: 2026/07/12 15:08:42 by falamlih         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "headers.h"

int main(int arc, char **arv)
{
	if (!ft_parsing(arc, arv))
		return (0);
	t_data data = ft_get_data(arv);
	printf("%d", data.d_cooldown);
}