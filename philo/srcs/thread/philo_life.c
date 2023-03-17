/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_life.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rsabbah <rsabbah@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/08 14:14:07 by rsabbah           #+#    #+#             */
/*   Updated: 2023/03/17 12:06:56 by rsabbah          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/**
 * @brief unlocking the forks mutex.

 * @param philo a struct sontainig the current philo's data
*/
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

/**
 * @brief taking forks and handling the one philo case.
 * 
 * We use a lock order to prevent deadlocks.
 * 
 * @param philo a struct sontainig the current philo's data
*/
static void	lock_forks(t_philo *philo)
{
	pthread_mutex_t	*fork1;
	pthread_mutex_t	*fork2;

	fork1 = &philo->data->forks[philo->l_fork];
	fork2 = &philo->data->forks[philo->r_fork];
	pthread_mutex_lock(fork1);
	print_log(FORK_LOG, philo, NOFPRINT);
	if (philo->l_fork == philo->r_fork)
		return (thread_pause(philo, philo->time.die - 1));
	pthread_mutex_lock(fork2);
	print_log(FORK_LOG, philo, NOFPRINT);
}

/**
 * @brief adding a meal to the philo's meal count
 * and reseting the last meal value.

 * @param philo a struct sontainig the current philo's data
*/
static void	philo_meal(t_philo *philo)
{
	lock_forks(philo);
	if (philo->stop)
		return (unlock_forks(philo));
	print_log(EAT_LOG, philo, NOFPRINT);
	pthread_mutex_lock(&philo->infos);
	philo->last_meal = timestamp();
	pthread_mutex_unlock(&philo->infos);
	philo->meal_count++;
	check(philo, FULL);
	thread_pause(philo, philo->time.eat);
	print_log(SLEEP_LOG, philo, NOFPRINT);
	unlock_forks(philo);
}

int	sync_start(t_philo *philo, pthread_t *th_monitor)
{
	pthread_mutex_lock(&philo->sync);
	if (pthread_create(th_monitor, NULL, monitor, philo) != 0)
	{
		pthread_mutex_unlock(&philo->sync);
		return (FAILURE);
	}
	pthread_mutex_lock(&philo->data->mutex[START]);
	philo->last_meal = philo->data->t0;
	pthread_mutex_unlock(&philo->sync);
	pthread_mutex_unlock(&philo->data->mutex[START]);
	return (SUCCESS);
}

/**
 * @brief thread routine for the philos. We create the monitor thread 
 * and execute philos actions while no STOP signal is encounterd.

 * * We delay the odd ones to prevent philos taking forks at the same time

 * @param arg the philosopher's data
*/
void	*philo_life(void *arg)
{
	t_philo		*philo;
	pthread_t	th_monitor;

	philo = (t_philo *)arg;
	if (sync_start(philo, &th_monitor) == FAILURE)
		return (NULL);
	if (philo->id % 2 == 1)
		usleep(5000);
	while (philo->stop == false)
	{
		philo_meal(philo);
		if (philo->stop)
			break ;
		thread_pause(philo, philo->time.sleep);
		print_log(THINK_LOG, philo, NOFPRINT);
	}
	pthread_join(th_monitor, NULL);
	return (NULL);
}
