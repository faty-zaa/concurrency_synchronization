/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   headers.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: falamlih <falamlih@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/12 11:53:13 by falamlih          #+#    #+#             */
/*   Updated: 2026/07/25 19:03:04 by falamlih         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HEADERS_H
# define HEADERS_H

# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/time.h>
# include <unistd.h>

typedef struct s_coder	t_coder;

typedef struct s_config
{
	unsigned int		n_coders;
	unsigned int		t_burnout;
	unsigned int		t_compile;
	unsigned int		t_debug;
	unsigned int		t_refactor;
	unsigned int		compiles_required;
	unsigned int		dongle_cooldown;
	char				*scheduler;
}						t_config;

typedef struct s_dongle
{
	pthread_mutex_t		mutex_dongle;
	unsigned int		state;
	unsigned int		cooldown;
	unsigned int		id;

}						t_dongle;

typedef struct s_system
{
	t_coder				*coders;
	t_dongle			*dongles;
	t_config			config;
	pthread_mutex_t		mutex;
	unsigned int		starting_time;

}						t_system;

typedef struct s_coder
{
	pthread_t			thread;
	unsigned int		coder_id;
	unsigned int		compile_count;
	long				last_compile;
	pthread_mutex_t		mutex_coder;
	t_dongle			*left;
	t_dongle			*right;
	t_system			*system;
}						t_coder;

int						ft_check_args(char **arv, int count);
int						ft_parsing(int arc, char **arv);
t_config				ft_get_config(char **arv);
long					ft_atoi(const char *nptr);
char					*ft_tolower(char *c);
int						ft_isalpha(char *c);
size_t					ft_isalpha_num(char *c);
void					*simulation(void *arg);
void					creat_coders(t_system *system);
void					init_system(t_system *system, t_config *config);
void					join_threads(t_system *system);
long					get_time_ms(void);
void					take_dongles(t_coder *coder);
void					compiling(t_coder *coder);
void					refactoring(t_coder *coder);
void					debugging(t_coder *coder);
void					burnout(t_coder *coder);
void	relase_dongles(t_coder *coder);

#endif
