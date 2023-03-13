/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_life.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rsabbah <rsabbah@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/08 14:14:07 by rsabbah           #+#    #+#             */
/*   Updated: 2023/03/09 19:45:45 by rsabbah          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	unlock_forks(t_philo *philo)
{
	if (philo->l_fork == philo->r_fork)
		pthread_mutex_unlock(&philo->data->forks[philo->l_fork]);
	else
	{
		pthread_mutex_unlock(&philo->data->forks[philo->l_fork]);
		pthread_mutex_unlock(&philo->data->forks[philo->r_fork]);
	}
}

void	lock_forks(t_philo *philo)
{
	pthread_mutex_t	*fork1;
	pthread_mutex_t	*fork2;

	if (philo->id % 2 == 1)
		usleep(1000);
	fork1 = &philo->data->forks[ft_min(philo->l_fork, philo->r_fork)];
	fork2 = &philo->data->forks[ft_max(philo->l_fork, philo->r_fork)];
	pthread_mutex_lock(fork1);
	check(philo, DEATH + SIGSTOP);
	print_log(FORK_LOG, philo);
	if (philo->l_fork == philo->r_fork)
	{
		thread_pause(philo, philo->time.die - 1);
		return (print_log(DEATH_LOG, philo));
	}
	pthread_mutex_lock(fork2);
	check(philo, DEATH + SIGSTOP);
	print_log(FORK_LOG, philo);
}

void	philo_eat(t_philo *philo)
{
	lock_forks(philo);
	if (philo->sig == STOP)
		return (unlock_forks(philo));
	print_log(EAT_LOG, philo);
	pthread_mutex_lock(&philo->infos);
	philo->last_meal = timestamp();
	pthread_mutex_unlock(&philo->infos);
	philo->meal_count++;
	pthread_mutex_lock(&philo->data->mutex[COUNT]);
	if (philo->meal_count == philo->data->max_meal)
		philo->data->full_count++;
	pthread_mutex_unlock(&philo->data->mutex[COUNT]);
	check(philo, FULL + SIGSTOP);
	thread_pause(philo, philo->time.eat);
	print_log(SLEEP_LOG, philo);
	unlock_forks(philo);
}

void	*philo_life(void *arg)
{
	t_philo		*philo;
	pthread_t	th_monitor;

	philo = (t_philo *)arg;
	philo->last_meal = philo->data->t0;
	if (pthread_create(&th_monitor, NULL, monitor, philo) != 0)
		return (NULL);
	pthread_detach(th_monitor);
	while (philo->sig == CONTINUE)
	{
		philo_eat(philo);
		if (philo->sig == STOP)
			break ;
		thread_pause(philo, philo->time.sleep);
		print_log(THINK_LOG, philo);
	}
	return (NULL);
}
