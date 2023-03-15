/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_life.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rsabbah <rsabbah@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/15 12:39:08 by rsabbah           #+#    #+#             */
/*   Updated: 2023/03/15 19:00:49 by rsabbah          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	*monitor(void *arg)
{
	bool	stop;
	int		status;
	t_philo	*philo;

	stop = false;
	philo = (t_philo *)arg;
	philo->last_meal = philo->data->time.t0;
	if (philo->id == 1)
		(cleanup(philo->data), exit(DEAD));
	while (stop == false)
	{
		pthread_mutex_lock(&philo->infos);
		if (timestamp() - philo->last_meal >= philo->data->time.die)
		{
			philo->stop = true;
			print_log(DEATH_LOG, philo);
			stop = true;
		}
		pthread_mutex_unlock(&philo->infos);
		if (stop)
			(cleanup(philo->data), exit(DEAD));
		waitpid(-1, &status, 0);
		if (WEXITSTATUS(status) == DEAD)
		{
			stop = true;
			pthread_mutex_lock(&philo->infos);
			philo->stop = true;
			pthread_mutex_unlock(&philo->infos);
		}
	}
	return (NULL);
}

int	philo_life(t_data *data, int i)
{
	pthread_t	th_monitor;

	if (pthread_create(&th_monitor, NULL, monitor, &data->philo[i]) != 0)
		(cleanup(data), exit(FAILURE));
	while (data->philo[i].sig == CONTINUE)
	{
		//eat
		//sleep
		//think
	}
	cleanup(data);
	exit(DEAD);
}
