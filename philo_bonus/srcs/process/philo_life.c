/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_life.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rsabbah <rsabbah@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/15 12:39:08 by rsabbah           #+#    #+#             */
/*   Updated: 2023/03/20 18:22:39 by rsabbah          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	philo_full(t_philo *philo)
{
	philo->meal_count++;
	if (philo->meal_count == philo->data->max_meal)
		sem_post(philo->data->count);
}

void	philo_meal(t_philo *philo)
{
	sem_wait(philo->data->forks);
	print_log(FORK_LOG, philo);
	if (philo->data->philo_nb == 1)
		return (process_pause(philo, philo->data->time.die));
	sem_wait(philo->data->forks);
	print_log(FORK_LOG, philo);
	pthread_mutex_lock(&philo->infos);
	philo->last_meal = timestamp();
	pthread_mutex_unlock(&philo->infos);
	philo_full(philo);
	print_log(EAT_LOG, philo);
	process_pause(philo, philo->data->time.eat);
	print_log(SLEEP_LOG, philo);
	sem_post(philo->data->forks);
	sem_post(philo->data->forks);
}

int	start_threads(t_philo *philo, pthread_t *th_monitor, pthread_t *th_stop)
{
	if (pthread_create(th_monitor, NULL, monitor, philo) != 0)
		return (FAILURE);
	if (pthread_create(th_stop, NULL, stop, philo) != 0)
	{
		pthread_join(*th_monitor, NULL);
		return (FAILURE);
	}
	return (SUCCESS);
}

void	check(t_philo *philo, bool *stop)
{
	pthread_mutex_lock(&philo->end);
	if (philo->stop == true)
		*stop = true;
	pthread_mutex_unlock(&philo->end);
}

void	philo_life(t_philo *philo)
{
	pthread_t	th_monitor;
	pthread_t	th_stop;
	bool		stop;

	stop = false;
	philo->last_meal = philo->data->time.t0;
	if (philo->id % 2 == 1)
		usleep(5000);
	if (start_threads(philo, &th_monitor, &th_stop) == FAILURE)
	{
		cleanup(philo->data);
		exit(print_error(THREAD_ERR, "philo_life.c:69"));
	}
	while (stop == false)
	{
		print_log(THINK_LOG, philo);
		process_pause(philo, philo->data->time.think);
		philo_meal(philo);
		process_pause(philo, philo->data->time.sleep);
		check(philo, &stop);
	}
	pthread_join(th_monitor, NULL);
	pthread_join(th_stop, NULL);
	cleanup(philo->data);
	exit(SUCCESS);
}
	