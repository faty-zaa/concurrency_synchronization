/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   headers.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: falamlih <falamlih@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/12 11:53:13 by falamlih          #+#    #+#             */
/*   Updated: 2026/07/15 16:16:02 by falamlih         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HEADERS_H
# define HEADERS_H

# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>

typedef struct s_data
{
	unsigned int	n_coders;
	unsigned int	t_burnout;
	unsigned int	t_compile;
	unsigned int	t_debug;
	unsigned int	t_refactor;
	unsigned int	n_required;
	unsigned int	d_cooldown;
	char			*scheduler;
}					t_data;

typedef struct s_dongle
{
	unsigned int	state;
	unsigned int	cooldown;

}					t_dongle;
typedef struct s_coder
{
	unsigned int	coder_id;
	unsigned int	n_compile;
	unsigned int	start_compile;
	unsigned int	time_compile;
	unsigned int	time_debug;
	unsigned int	time_refactor;
	t_dongle	*left;
	t_dongle	*right;
}					t_coder;


int					ft_check_args(char **arv, int count);
int					ft_parsing(int arc, char **arv);
t_data				ft_get_data(char **arv);
long				ft_atoi(const char *nptr);
char				*ft_tolower(char *c);
int					ft_isalpha(char *c);
size_t				ft_isalpha_num(char *c);

#endif
