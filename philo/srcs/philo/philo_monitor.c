/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_monitor.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rsabbah <rsabbah@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/22 13:40:56 by rsabbah           #+#    #+#             */
/*   Updated: 2023/03/22 13:41:20 by rsabbah          ###   ########.fr       */
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

void	*philo_monitor(void *arg)
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
