/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_stop.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rsabbah <rsabbah@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/22 11:12:10 by rsabbah           #+#    #+#             */
/*   Updated: 2023/03/22 13:12:35 by rsabbah          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	*philo_stop(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	sem_wait(philo->data->end);
	sem_post(philo->data->end);
	sem_post(philo->data->count);
	pthread_mutex_lock(&philo->infos);
	philo->stop = true;
	pthread_mutex_unlock(&philo->infos);
	return (NULL);
}
