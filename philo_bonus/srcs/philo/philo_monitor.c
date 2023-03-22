/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_monitor.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rsabbah <rsabbah@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/22 11:11:29 by rsabbah           #+#    #+#             */
/*   Updated: 2023/03/22 13:18:47 by rsabbah          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	philo_death(t_philo *philo, bool *stop)
{
	sem_wait(philo->data->stop);
	pthread_mutex_lock(&philo->infos);
	if (philo->stop == false)
		print_log(DEATH_LOG, philo);
	philo->stop = true;
	pthread_mutex_unlock(&philo->infos);
	sem_post(philo->data->end);
	usleep(1000);
	sem_post(philo->data->stop);
	*stop = true;
}

void	*philo_monitor(void *arg)
{
	t_philo	*philo;
	bool	stop;
	bool	dead;

	philo = (t_philo *)arg;
	stop = false;
	dead = false;
	while (stop == false)
	{
		pthread_mutex_lock(&philo->infos);
		if (timestamp() - philo->last_meal >= philo->data->time.die)
			dead = true;
		pthread_mutex_unlock(&philo->infos);
		if (dead)
			philo_death(philo, &stop);
		else
			philo_check(philo, &stop);
		usleep(5000);
	}
	return (NULL);
}
