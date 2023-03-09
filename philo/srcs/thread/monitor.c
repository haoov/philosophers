/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rsabbah <rsabbah@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/08 15:17:22 by rsabbah           #+#    #+#             */
/*   Updated: 2023/03/09 16:46:12 by rsabbah          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	check_death(t_philo *philo)
{
	if (timestamp() - philo->last_meal >= philo->time.die)
	{
		pthread_mutex_lock(&philo->data->mutex[END]);
		philo->data->sig = STOP;
		philo->dead = true;
		pthread_mutex_unlock(&philo->data->mutex[END]);
	}
}

void	check_full(t_philo *philo)
{
	pthread_mutex_lock(&philo->data->mutex[COUNT]);
	if (philo->data->full_count == philo->data->philo_nb)
	{
		pthread_mutex_lock(&philo->data->mutex[END]);
		philo->data->sig = STOP;
		philo->sig = STOP;
		pthread_mutex_unlock(&philo->data->mutex[END]);
	}
	pthread_mutex_unlock(&philo->data->mutex[COUNT]);
}

void	monitor(t_philo *philo)
{
	pthread_mutex_lock(&philo->data->mutex[END]);
	if (philo->data->sig == STOP)
		philo->sig = STOP;
	pthread_mutex_unlock(&philo->data->mutex[END]);
	if (philo->sig == CONTINUE)
		check_death(philo);
	if (philo->sig == CONTINUE)
		check_full(philo);
}
