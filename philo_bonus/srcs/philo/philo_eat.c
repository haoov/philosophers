/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_eat.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rsabbah <rsabbah@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/22 11:00:20 by rsabbah           #+#    #+#             */
/*   Updated: 2023/03/22 11:44:47 by rsabbah          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	philo_full(t_philo *philo, bool *stop)
{
	philo->meal_count++;
	if (philo->meal_count == philo->data->max_meal)
		sem_post(philo->data->count);
	philo_check(philo, stop);
}

void	philo_eat(t_philo *philo, bool *stop)
{
	philo_log(philo, EAT_LOG);
	pthread_mutex_lock(&philo->infos);
	philo->last_meal = timestamp();
	pthread_mutex_unlock(&philo->infos);
	philo_wait(philo->data->time.eat);
	philo_full(philo, stop);
	if (*stop)
		return (philo_put_down_fork(philo, 2));
	philo_log(philo, SLEEP_LOG);
	philo_put_down_fork(philo, 2);
	philo_wait(philo->data->time.sleep);
}
