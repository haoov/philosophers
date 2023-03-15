/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rsabbah <rsabbah@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/15 10:00:37 by rsabbah           #+#    #+#             */
/*   Updated: 2023/03/15 11:30:50 by rsabbah          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	philo_death(t_philo *philo, bool *stop)
{
	t_signal	sig;

	pthread_mutex_lock(&philo->data->mutex[END]);
	if (philo->data->sig == STOP)
		sig = NOFPRINT;
	else
		sig = FPRINT;
	philo->data->sig = STOP;
	pthread_mutex_unlock(&philo->data->mutex[END]);
	print_log(DEATH_LOG, philo, sig);
	*stop = true;
}

/**
 * @brief monitoring the philo to check if he is dead or not

 * @param arg The philosophers data
*/
void	*monitor(void *arg)
{
	t_philo	*philo;
	bool	stop;

	philo = (t_philo *)arg;
	philo->last_meal = philo->data->t0;
	stop = false;
	while (stop == false)
	{
		pthread_mutex_lock(&philo->infos);
		if (timestamp() - philo->last_meal >= philo->time.die)
			philo_death(philo, &stop);
		pthread_mutex_unlock(&philo->infos);
		usleep(5000);
	}
	return (NULL);
}
