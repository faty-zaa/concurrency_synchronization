/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   headers.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: falamlih <falamlih@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/12 11:53:13 by falamlih          #+#    #+#             */
/*   Updated: 2026/07/20 22:48:06 by falamlih         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HEADERS_H
# define HEADERS_H

# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>

/*configuration from the input*/
typedef struct s_config
{
	unsigned int	n_coders;
	unsigned int	t_burnout;
	unsigned int	t_compile;
	unsigned int	t_debug;
	unsigned int	t_refactor;
	unsigned int	compiles_required;
	unsigned int	dongle_cooldown;
	char			*scheduler;
}					t_config;

/*dongle struct*/
typedef struct s_dongle
{
	pthread_mutex_t mutex;
	unsigned int	state;
	unsigned int	cooldown;

}					t_dongle;

/*coder struct*/
typedef struct s_coder
{
	pthread_t thread;
	unsigned int	coder_id;
	unsigned int	compile_count;
	unsigned int	last_compile;
	// unsigned int	time_tcompile;
	// unsigned int	time_tdebug;
	// unsigned int	time_trefactor;
	// unsigned int	time_tburnout;
	t_dongle	*left;
	t_dongle	*right;
}					t_coder;


int					ft_check_args(char **arv, int count);
int					ft_parsing(int arc, char **arv);
t_config				ft_get_config(char **arv);
long				ft_atoi(const char *nptr);
char				*ft_tolower(char *c);
int					ft_isalpha(char *c);
size_t				ft_isalpha_num(char *c);

#endif
