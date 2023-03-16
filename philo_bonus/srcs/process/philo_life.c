/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_life.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rsabbah <rsabbah@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/15 12:39:08 by rsabbah           #+#    #+#             */
/*   Updated: 2023/03/16 17:23:30 by rsabbah          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	*monitor(void *arg)
{
	t_philo	*philo;
	bool	dead;

	philo = (t_philo *)arg;
	dead = false;
	while (dead == false)
	{
		pthread_mutex_lock(&philo->infos);
		if (timestamp() - philo->last_meal >= philo->data->time.die)
		{
			print_log(DEATH_LOG, philo, LOCK);
			sem_post(philo->data->stop);
			dead = true;
		}
		pthread_mutex_unlock(&philo->infos);
		usleep(5000);
	}
	return (NULL);
}

void	philo_full(t_philo *philo)
{
	philo->meal_count++;
	if (philo->meal_count == philo->data->max_meal)
		sem_post(philo->data->count);
}

void	philo_meal(t_philo *philo)
{
	sem_wait(philo->data->forks);
	print_log(FORK_LOG, philo, UNLOCK);
	sem_wait(philo->data->forks);
	print_log(FORK_LOG, philo, UNLOCK);
	pthread_mutex_lock(&philo->infos);
	philo->last_meal = timestamp();
	pthread_mutex_unlock(&philo->infos);
	philo_full(philo);
	print_log(EAT_LOG, philo, UNLOCK);
	process_pause(philo, philo->data->time.eat);
	print_log(SLEEP_LOG, philo, UNLOCK);
	sem_post(philo->data->forks);
	sem_post(philo->data->forks);
}

void	philo_life(t_philo *philo)
{
	pthread_t	th_monitor;

	philo->last_meal = philo->data->time.t0;
	if (philo->id % 2 == 1)
		usleep(5000);
	if (pthread_create(&th_monitor, NULL, monitor, philo) != 0)
	{
		cleanup(philo->data);
		exit(print_error(THREAD_ERR, "philo_life.c:69"));
	}
	while (philo)
	{
		philo_meal(philo);
		process_pause(philo, philo->data->time.sleep);
		print_log(THINK_LOG, philo, UNLOCK);
	}
}
