/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rsabbah <rsabbah@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/03 14:16:00 by rsabbah           #+#    #+#             */
/*   Updated: 2023/03/09 18:24:32 by rsabbah          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

/**********INCLUDES***********/

# include <unistd.h>
# include <stdio.h>
# include <pthread.h>
# include <stdlib.h>
# include <stdbool.h>
# include <string.h>
# include <sys/time.h>

/***********DEFINES***********/

# define SUCCESS	0
# define FAILURE	1
# define HELP		"--help"
# define ARG_ERR	"Invalid argument"
# define ARGN_ERR	"Invalid number of arguments"
# define MALLOC_ERR	"Malloc failed"

# define DEATH_LOG	"died"
# define THINK_LOG	"is thinking"
# define SLEEP_LOG	"is sleeping"
# define EAT_LOG	"is eating"
# define FORK_LOG	"has taken a fork"

/********ENUM AND STRUCT********/

typedef enum e_check
{
	FULL = 1,
	SIGSTOP = 2
}t_check;

typedef enum e_signal
{
	CONTINUE,
	STOP,
	FPRINT,
	NOFPRINT
}t_signal;

typedef enum e_mutex
{
	LOG,
	COUNT,
	END
}t_mutex;

typedef struct s_time
{
	int	die;
	int	eat;
	int	sleep;
}t_time;

typedef struct s_philo
{
	int				id;
	int				last_meal;
	int				meal_count;
	int				l_fork;
	int				r_fork;
	pthread_mutex_t	infos;
	pthread_mutex_t	start;
	t_time			time;
	t_signal		sig;
	struct s_data	*data;
	pthread_t		th;
}t_philo;

typedef struct s_data
{
	int				philo_nb;
	int				max_meal;
	int				full_count;
	int				t0;
	t_time			time;
	t_signal		sig;
	pthread_mutex_t	mutex[3];
	pthread_mutex_t	*forks;
	t_philo			*philo;
}t_data;

/********DECLARATION*********/

int		init(t_data *data, int argc, char **argv);

int		threads(t_data *data);
void	*philo_life(void *arg);
void	check(t_philo *philo, t_check check);
void	*monitor(void *arg);

int		timestamp(void);
void	thread_pause(t_philo *philo, int time);

void	cleanup(t_data data);

int		ft_atoi(const char *str);
int		ft_strcmp(const char *a, const char *b);
int		ft_strlen(char *str);
int		only_digit(char *str);
void	*ft_calloc(int nb, int size);

void	print_log(char *log, t_philo *philo, t_signal flag);
void	print_helper(void);
void	print_error(char *error, char *infos);

#endif
