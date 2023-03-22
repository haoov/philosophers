/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_eat.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rsabbah <rsabbah@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/22 13:52:23 by rsabbah           #+#    #+#             */
/*   Updated: 2023/03/22 14:17:20 by rsabbah          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	philo_full(t_philo *philo)
{
	pthread_mutex_lock(&philo->data->mtx_count);
	if (philo->meal_count == philo->data->max_meal)
	{
		philo->data->full_count++;
		if (philo->data->full_count == philo->data->philo_nb)
		{
			pthread_mutex_lock(&philo->data->mtx_stop);
			philo->data->stop = true;
			philo->stop = true;
			pthread_mutex_unlock(&philo->data->mtx_stop);
		}
	}
	pthread_mutex_unlock(&philo->data->mtx_count);
}

void	philo_eat(t_philo *philo)
{
	philo_log(philo, EAT_LOG);
	pthread_mutex_lock(&philo->infos);
	philo->last_meal = timestamp();
	pthread_mutex_unlock(&philo->infos);
	philo->meal_count++;
	philo_full(philo);
	philo_wait(philo->time.eat);
	philo_log(philo, SLEEP_LOG);
	philo_put_down_forks(philo);
	philo_wait(philo->time.sleep);
}
