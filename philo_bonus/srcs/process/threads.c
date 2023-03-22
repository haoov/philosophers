/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rsabbah <rsabbah@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/20 17:06:16 by rsabbah           #+#    #+#             */
/*   Updated: 2023/03/20 18:26:43 by rsabbah          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	*stop(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	sem_wait(philo->data->end);
	sem_wait(philo->data->stop);
	sem_post(philo->data->end);
	sem_post(philo->data->count);
	pthread_mutex_lock(&philo->infos);
	philo->stop = true;
	pthread_mutex_lock(&philo->infos);
	sem_post(philo->data->stop);
	return (NULL);
}

void	philo_death(t_philo *philo, bool *stop)
{
	sem_wait(philo->data->stop);
	if (philo->stop == false)
		print_log(DEATH_LOG, philo);
	philo->stop = true;
	sem_post(philo->data->end);
	sem_post(philo->data->stop);
	*stop = true;
}

void	*monitor(void *arg)
{
	t_philo	*philo;
	bool	stop;

	philo = (t_philo *)arg;
	stop = false;
	while (stop == false)
	{
		pthread_mutex_lock(&philo->infos);
		if (timestamp() - philo->last_meal >= philo->data->time.die)
			philo_death(philo, &stop);
		pthread_mutex_unlock(&philo->infos);
		check(philo, &stop);
		usleep(5000);
	}
	return (NULL);
}
