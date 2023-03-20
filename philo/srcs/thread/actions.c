/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rsabbah <rsabbah@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/20 15:24:43 by rsabbah           #+#    #+#             */
/*   Updated: 2023/03/20 16:34:07 by rsabbah          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	philo_log(t_philo *philo, char *log)
{
	pthread_mutex_lock(&philo->data->mtx_stop);
	if (philo->data->stop == false)
		print_log(log, philo);
	else
		philo->stop = true;
	pthread_mutex_unlock(&philo->data->mtx_stop);
}

static void	unlock_forks(t_philo *philo)
{
	if (philo->l_fork == philo->r_fork)
		pthread_mutex_unlock(&philo->data->forks[philo->l_fork]);
	else
	{
		pthread_mutex_unlock(&philo->data->forks[philo->l_fork]);
		pthread_mutex_unlock(&philo->data->forks[philo->r_fork]);
	}
}

static void	lock_forks(t_philo *philo)
{
	pthread_mutex_t	*fork1;
	pthread_mutex_t	*fork2;

	fork1 = &philo->data->forks[ft_min(philo->l_fork, philo->r_fork)];
	fork2 = &philo->data->forks[ft_max(philo->r_fork, philo->l_fork)];
	pthread_mutex_lock(fork1);
	philo_log(philo, FORK_LOG);
	if (philo->l_fork == philo->r_fork)
		return (thread_pause(philo->time.die + 5));
	pthread_mutex_lock(fork2);
	philo_log(philo, FORK_LOG);
}

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

void	philo_meal(t_philo *philo)
{
	lock_forks(philo);
	if (philo->stop)
		return (unlock_forks(philo));
	philo_log(philo, EAT_LOG);
	pthread_mutex_lock(&philo->infos);
	philo->last_meal = timestamp();
	pthread_mutex_unlock(&philo->infos);
	philo->meal_count++;
	philo_full(philo);
	thread_pause(philo->time.eat);
	philo_log(philo, SLEEP_LOG);
	unlock_forks(philo);
}
