/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_life.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rsabbah <rsabbah@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/08 14:14:07 by rsabbah           #+#    #+#             */
/*   Updated: 2023/03/20 16:39:46 by rsabbah          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	philo_death(t_philo *philo, bool *dead)
{
	pthread_mutex_lock(&philo->data->mtx_stop);
	if (philo->data->stop == false)
		print_log(DEATH_LOG, philo);
	philo->data->stop = true;
	pthread_mutex_unlock(&philo->data->mtx_stop);
	*dead = true;
}

void	*monitor(void *arg)
{
	t_philo	*philo;
	bool	dead;

	philo = (t_philo *)arg;
	dead = false;
	while (dead == false)
	{
		pthread_mutex_lock(&philo->infos);
		if (timestamp() - philo->last_meal >= philo->time.die)
			philo_death(philo, &dead);
		pthread_mutex_unlock(&philo->infos);
		usleep(5000);
	}
	return (NULL);
}

static int	start_monitor(t_philo *philo, pthread_t *th_monitor)
{
	if (pthread_create(th_monitor, NULL, monitor, philo) != 0)
	{
		pthread_mutex_lock(&philo->data->mtx_stop);
		philo->data->stop = true;
		pthread_mutex_unlock(&philo->data->mtx_stop);
		print_error(THREAD_ERR, "philo_life.c");
		return (FAILURE);
	}
	return (SUCCESS);
}

void	*philo_life(void *arg)
{
	t_philo		*philo;
	pthread_t	th_monitor;

	philo = (t_philo *)arg;
	philo->last_meal = philo->data->t0;
	if (start_monitor(philo, &th_monitor) == FAILURE)
		return (NULL);
	if (philo->id % 2 == 1)
		usleep(5000);
	while (philo->stop == false)
	{
		philo_log(philo, THINK_LOG);
		thread_pause(philo->time.think);
		philo_meal(philo);
		if (philo->stop)
			break ;
		thread_pause(philo->time.sleep);
	}
	pthread_join(th_monitor, NULL);
	return (NULL);
}
