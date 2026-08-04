/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   headers.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: falamlih <falamlih@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/12 11:53:13 by falamlih          #+#    #+#             */
/*   Updated: 2026/08/04 06:22:20 by falamlih         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HEADERS_H
# define HEADERS_H

# include <pthread.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/time.h>
# include <unistd.h>

typedef struct s_coder	t_coder;
typedef struct s_heap
{
	t_coder				**array;
	unsigned int		size;
	unsigned int		capacity;
}						t_heap;

typedef struct s_queue
{
	t_coder				**array;
	unsigned int		size;
	unsigned int		capacity;
}						t_queue;

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
	pthread_cond_t		cond_dongle;
	bool		used;
	unsigned int		id;
	t_queue				fifo;
	t_heap				edf;
	t_coder				*current;
	char				*algo;
	bool				state;

}						t_dongle;

typedef struct s_system
{
	t_coder				*coders;
	pthread_t			monitor_thread;
	t_dongle			*dongles;
	t_config			config;
	pthread_mutex_t		print_mutex;
	long				starting_time;
	bool				stop;

	pthread_mutex_t		stop_mutex;
	char				*scheduler;

}						t_system;

typedef struct s_coder
{
	pthread_t			thread;
	pthread_mutex_t		mutex_coder;
	int					state;
	bool				waiting;
	unsigned int		coder_id;
	unsigned int		compile_count;
	long				last_compile;
	long				deadline;
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
void					cleanup_system(t_system *system);
long					get_time_ms(void);
void					take_dongle(t_dongle *dongle, t_coder *coder);
void					compiling(t_coder *coder);
void					refactoring(t_coder *coder);
void					debugging(t_coder *coder);
void					burnout(t_coder *coder);
void					relase_dongle(t_dongle *dongle);
long					deadline(t_coder *coder);
void					*monitor(void *args);
void					heap_init(t_heap *heap, int capacity);
void					heap_destroy(t_heap *heap);
void					heap_insert(t_heap *heap, t_coder *coder);
t_coder					*heap_pop(t_heap *heap);
void					queue_init(t_queue *queue, int capacity);
void					queue_destroy(t_queue *queue);
void					fifo_enqueue(t_queue *queue, t_coder *coder);
t_coder					*fifo_deque(t_queue *queue);
long					get_time(t_system *system);
long					count_burnout(long last);
void					system_stop(t_system *system);
bool					system_is_stopped(t_system *system);
void					burnout(t_coder *coder);
unsigned int			coder_compiles(t_coder *coder);
void					take_dongles(t_coder *coder);
void	relase_dongles(t_coder *coder);
#endif
