/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_life.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rsabbah <rsabbah@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/22 10:55:55 by rsabbah           #+#    #+#             */
/*   Updated: 2023/03/22 15:01:02 by rsabbah          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	start_threads(t_philo *philo, pthread_t *th_monitor, pthread_t *th_stop)
{
	if (pthread_create(th_monitor, NULL, philo_monitor, philo) != 0)
	{
		cleanup(philo->data);
		exit(FAILURE);
	}
	if (pthread_create(th_stop, NULL, philo_stop, philo) != 0)
	{
		pthread_join(*th_monitor, NULL);
		cleanup(philo->data);
		exit(FAILURE);
	}
}

void	philo_life(t_philo *philo)
{
	pthread_t	th_monitor;
	pthread_t	th_stop;
	bool		stop;

	stop = false;
	philo->last_meal = philo->data->time.t0;
	start_threads(philo, &th_monitor, &th_stop);
	if (philo->id % 2 == 1)
		usleep(50000);
	while (stop == false)
	{
		philo_think(philo, &stop);
		if (stop == false)
			philo_eat(philo, &stop);
	}
	pthread_join(th_monitor, NULL);
	pthread_join(th_stop, NULL);
	cleanup(philo->data);
	exit(SUCCESS);
}
