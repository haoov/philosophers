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

# include <unistd.h>
# include <stdio.h>
# include <pthread.h>
# include <stdlib.h>
# include <stdbool.h>
# include <string.h>
# include <sys/time.h>

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

typedef enum e_signal
{
	CONTINUE,
	STOP
}t_signal;

typedef enum e_mutex
{
	PRINT,
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
	bool			dead;
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

int		init(t_data *data, int argc, char **argv);

int		threads(t_data *data);
void	*philo_life(void *arg);
void	monitor(t_philo *philo);

int		timestamp(void);
void	thread_pause(t_philo *philo, int time);

void	cleanup(t_data data);

int		ft_atoi(const char *str);
int		ft_strcmp(const char *a, const char *b);
int		ft_strlen(char *str);
int		only_digit(char *str);
int		ft_max(int a, int b);
int		ft_min(int a, int b);
void	*ft_calloc(int nb, int size);

void	print_log(char *log, t_philo *philo);
void	print_helper(void);
void	print_error(char *error, char *infos);

#endif
