/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_life.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rsabbah <rsabbah@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/08 14:14:07 by rsabbah           #+#    #+#             */
/*   Updated: 2023/03/22 13:53:37 by rsabbah          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	start_monitor(t_philo *philo, pthread_t *th_monitor)
{
	if (pthread_create(th_monitor, NULL, philo_monitor, philo) != 0)
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
		philo_think(philo);
		if (philo->stop == false)
			philo_eat(philo);
	}
	pthread_join(th_monitor, NULL);
	return (NULL);
}
