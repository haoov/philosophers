/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rsabbah <rsabbah@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/08 14:08:36 by rsabbah           #+#    #+#             */
/*   Updated: 2023/03/17 12:10:26 by rsabbah          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/**
 * @brief wait for the threads to finish.
 * 
 * If th_nb is less than data.philo_nb it means pthread_create has failed. 
 * We then need to launch the threads using START mutex and put data.stop 
 * value to true to stop them using the END mutex.
 * 
 * @param data a pointer to the main data struct.
 * @param th_nb the number of threads that have been created.
*/
static void	thread_join(t_data *data, int th_nb)
{
	int	i;

	i = 0;
	if (th_nb < data->philo_nb)
	{
		data->t0 = timestamp();
		pthread_mutex_unlock(&data->mutex[START]);
		pthread_mutex_lock(&data->mutex[END]);
		data->stop = true;
		pthread_mutex_unlock(&data->mutex[END]);
		print_error(THREAD_ERR, "threads.c");
	}
	while (i < th_nb)
	{
		pthread_join(data->philo[i].th, NULL);
		i++;
	}
}

/**
 * @brief create all the philo_life threads and sync them.
 * 
 * The START mutex is used to sync all threads.
 * If pthread_create fails we wait the others before exiting.
 * 
 * @param data a pointer to the main data struct.
*/
int	threads(t_data *data)
{
	int	i;

	i = 0;
	pthread_mutex_lock(&data->mutex[START]);
	while (i < data->philo_nb)
	{
		if (pthread_create(&data->philo[i].th, NULL,
				philo_life, &data->philo[i]) != 0)
			return (thread_join(data, i), FAILURE);
		i++;
	}
	data->t0 = timestamp();
	pthread_mutex_unlock(&data->mutex[START]);
	thread_join(data, i);
	return (SUCCESS);
}
