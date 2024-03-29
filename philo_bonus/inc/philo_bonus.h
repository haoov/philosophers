/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rsabbah <rsabbah@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/15 11:06:27 by rsabbah           #+#    #+#             */
/*   Updated: 2023/03/22 13:15:00 by rsabbah          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_BONUS_H
# define PHILO_BONUS_H

/**********INCLUDES***********/

# include <unistd.h>
# include <stdio.h>
# include <pthread.h>
# include <stdlib.h>
# include <stdbool.h>
# include <string.h>
# include <sys/time.h>
# include <fcntl.h>
# include <sys/stat.h>
# include <semaphore.h>
# include <sys/types.h>
# include <signal.h>
# include <sys/wait.h>

/***********DEFINES***********/

# define SUCCESS	0
# define FAILURE	1
# define HELP		"--help"
# define ARG_ERR	"Invalid argument"
# define ARGN_ERR	"Invalid number of arguments"
# define MALLOC_ERR	"Malloc failed"
# define SEM_ERR	"sem_open failed"
# define FORK_ERR	"fork failed"
# define THREAD_ERR	"pthread_create failed"

# define DEATH_LOG	"died"
# define THINK_LOG	"is thinking"
# define SLEEP_LOG	"is sleeping"
# define EAT_LOG	"is eating"
# define FORK_LOG	"has taken a fork"

# define SEM_FORKS	"forks_semaphore"
# define SEM_STOP	"stop_semaphore"
# define SEM_COUNT	"count_semaphore"
# define SEM_END	"end_semaphore"
# define STOP		1
# define DEAD		2

/********ENUM AND STRUCT********/

typedef struct s_time
{
	int	t0;
	int	die;
	int	eat;
	int	sleep;
	int	think;
}t_time;

typedef struct s_philo
{
	int				id;
	int				last_meal;
	int				meal_count;
	bool			stop;
	pthread_mutex_t	infos;
	struct s_data	*data;
	pid_t			pid;
}t_philo;

typedef struct s_data
{
	int				philo_nb;
	int				max_meal;
	int				full_count;
	sem_t			*forks;
	sem_t			*count;
	sem_t			*stop;
	sem_t			*end;
	t_time			time;
	t_philo			*philo;
}t_data;

/********DECLARATION*********/

int		init(t_data *data, int argc, char **argv);

int		philosophers(t_data *data);
void	philo_life(t_philo *philo);
void	philo_think(t_philo *philo, bool *stop);
void	philo_eat(t_philo *philo, bool *stop);
void	philo_put_down_fork(t_philo *philo, int fork_nb);
void	*philo_monitor(void *arg);
void	*philo_stop(void *arg);
void	philo_check(t_philo *philo, bool *stop);
void	philo_log(t_philo *philo, char *log);
void	philo_wait(int time);

int		timestamp(void);

void	cleanup(t_data *data);

int		ft_atoi(const char *str);
int		ft_strcmp(const char *a, const char *b);
int		ft_strlen(char *str);
int		only_digit(char *str);
void	*ft_calloc(int nb, int size);

void	print_log(char *log, t_philo *philo);
void	print_helper(void);
int		print_error(char *error, char *infos);

#endif
