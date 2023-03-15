/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rsabbah <rsabbah@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/15 10:01:07 by rsabbah           #+#    #+#             */
/*   Updated: 2023/03/15 11:28:46 by rsabbah          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	check_full(t_philo *philo)
{
	pthread_mutex_lock(&philo->data->mutex[COUNT]);
	if (philo->meal_count == philo->data->max_meal)
		philo->data->full_count++;
	if (philo->data->full_count == philo->data->philo_nb)
	{
		pthread_mutex_lock(&philo->data->mutex[END]);
		philo->data->sig = STOP;
		philo->sig = STOP;
		pthread_mutex_unlock(&philo->data->mutex[END]);
	}
	pthread_mutex_unlock(&philo->data->mutex[COUNT]);
}

t_signal	check(t_philo *philo, t_check check)
{
	if (check == SIGSTOP)
	{
		pthread_mutex_lock(&philo->data->mutex[END]);
		if (philo->data->sig == STOP)
			philo->sig = STOP;
		pthread_mutex_unlock(&philo->data->mutex[END]);
	}
	if (check == FULL)
		check_full(philo);
	return (philo->sig);
}
