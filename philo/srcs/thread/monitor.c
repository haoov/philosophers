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

/**
 * @brief handling the philo's death. 
 * 
 * Using the END mutex, we put the data.stop value to true so 
 * that others philo stop.
 * 
 * If the data.stop value is already true then we send NOFPRINT 
 * (no force print) to print_Log() and the DEATH_LOG wont be printed.
 * FPRINT (force print) tells print_log() to print even if the 
 * data.stop value is true so that the DEATH_LOG can be printed.
 * 
 * @param philo a pointer to a truct containing the philo's data.
 * @param dead a pointer to a bool representing the philo's death.
*/
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
 * @brief monitoring the philo to check if he is dead or not.
 * 
 * The sync mutex is used to sync the monitor thread with his 
 * corresponding philo_life thread. (see philo_life.c)
 * The infos mutex protects the last_meal value.
 * We wait 5ms so that the thread is not always trying to lock 
 * the infos mutex resulting in possible speed lost.
 * 
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
