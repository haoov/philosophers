/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_think.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rsabbah <rsabbah@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/22 13:42:22 by rsabbah           #+#    #+#             */
/*   Updated: 2023/03/22 14:17:43 by rsabbah          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	philo_take_forks(t_philo *philo)
{
	pthread_mutex_t	*fork1;
	pthread_mutex_t	*fork2;

	fork1 = &philo->data->forks[ft_min(philo->l_fork, philo->r_fork)];
	fork2 = &philo->data->forks[ft_max(philo->r_fork, philo->l_fork)];
	pthread_mutex_lock(fork1);
	philo_log(philo, FORK_LOG);
	if (philo->l_fork == philo->r_fork)
		return (philo_wait(philo->time.die));
	pthread_mutex_lock(fork2);
	philo_log(philo, FORK_LOG);
}

void	philo_think(t_philo *philo)
{
	philo_log(philo, THINK_LOG);
	philo_wait(philo->time.think);
	philo_take_forks(philo);
	if (philo->stop)
		return (philo_put_down_forks(philo));
}
