/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rsabbah <rsabbah@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/15 10:00:37 by rsabbah           #+#    #+#             */
/*   Updated: 2023/03/17 12:07:11 by rsabbah          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	philo_death(t_philo *philo, bool *dead)
{
	t_signal	sig;

	pthread_mutex_lock(&philo->data->mutex[END]);
	if (philo->data->stop)
		sig = NOFPRINT;
	else
		sig = FPRINT;
	philo->data->stop = true;
	pthread_mutex_unlock(&philo->data->mutex[END]);
	print_log(DEATH_LOG, philo, sig);
	*dead = true;
}

/**
 * @brief monitoring the philo to check if he is dead or not

 * @param arg The philosophers data
*/
void	*monitor(void *arg)
{
	t_philo	*philo;
	bool	dead;

	philo = (t_philo *)arg;
	pthread_mutex_lock(&philo->sync);
	pthread_mutex_unlock(&philo->sync);
	dead = false;
	while (dead == false)
	{
		pthread_mutex_lock(&philo->infos);
		if (timestamp() - philo->last_meal >= philo->time.die)
			philo_death(philo, &dead);
		pthread_mutex_unlock(&philo->infos);
		usleep(5000);
	}
	return (NULL);
}
