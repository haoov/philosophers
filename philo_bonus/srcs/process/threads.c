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
	sem_wait(philo->data->stop);
	sem_post(philo->data->stop);
	sem_post(philo->data->count);
	pthread_mutex_lock(&philo->end);
	philo->stop = true;
	pthread_mutex_unlock(&philo->end);
	return (NULL);
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
		if (timestamp() - philo->last_meal >= philo->data->time.die)
		{
			print_log(DEATH_LOG, philo);
			sem_post(philo->data->stop);
			dead = true;
		}
		pthread_mutex_unlock(&philo->infos);
		usleep(5000);
	}
	return (NULL);
}
