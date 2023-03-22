/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_life.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rsabbah <rsabbah@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/15 12:39:08 by rsabbah           #+#    #+#             */
/*   Updated: 2023/03/20 18:22:39 by rsabbah          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	philo_full(t_philo *philo, bool *stop)
{
	philo->meal_count++;
	if (philo->meal_count == philo->data->max_meal)
		sem_post(philo->data->count);
	check(philo, stop);
}

void	philo_eat(t_philo *philo, bool *stop)
{
	philo_log(philo, EAT_LOG);
	pthread_mutex_lock(&philo->infos);
	philo->last_meal = timestamp();
	pthread_mutex_unlock(&philo->infos);
	philo_full(philo, stop);
	process_pause(philo, philo->data->time.eat);
	philo_log(philo, SLEEP_LOG);
	sem_post(philo->data->forks);
	sem_post(philo->data->forks);
}

int	start_threads(t_philo *philo, pthread_t *th_monitor, pthread_t *th_stop)
{
	if (pthread_create(th_monitor, NULL, monitor, philo) != 0)
		return (FAILURE);
	if (pthread_create(th_stop, NULL, stop, philo) != 0)
	{
		pthread_join(*th_monitor, NULL);
		return (FAILURE);
	}
	return (SUCCESS);
}

void	check(t_philo *philo, bool *stop)
{
	pthread_mutex_lock(&philo->infos);
	if (philo->stop == true)
		*stop = true;
	pthread_mutex_unlock(&philo->infos);
}

void	put_down_forks(t_philo *philo, int fork_nb)
{
	int	i;

	i = 0;
	while (i < fork_nb)
	{
		sem_post(philo->data->forks);
		i++;
	}
}

void	philo_think(t_philo *philo, bool *stop)
{
	int	i;

	i = 0;
	philo_log(philo, THINK_LOG);
	process_pause(philo, philo->data->time.think);
	while (i < 2)
	{
		sem_wait(philo->data->forks);
		if (philo->data->philo_nb == 1)
			process_pause(philo, philo->data->time.die);
		check(philo, stop);
		if (*stop)
			return (put_down_forks(philo, i));
		philo_log(philo, FORK_LOG);
		i++;
	}
}

void	philo_life(t_philo *philo)
{
	pthread_t	th_monitor;
	pthread_t	th_stop;
	bool		stop;

	stop = false;
	philo->last_meal = philo->data->time.t0;
	if (philo->id % 2 == 1)
		usleep(5000);
	if (start_threads(philo, &th_monitor, &th_stop) == FAILURE)
	{
		cleanup(philo->data);
		exit(print_error(THREAD_ERR, "philo_life.c:69"));
	}
	while (stop == false)
	{
		philo_think(philo, &stop);
		philo_eat(philo, &stop);
		process_pause(philo, philo->data->time.sleep);
		check(philo, &stop);
	}
	pthread_join(th_monitor, NULL);
	pthread_join(th_stop, NULL);
	cleanup(philo->data);
	exit(SUCCESS);
}
	