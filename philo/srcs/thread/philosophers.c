/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rsabbah <rsabbah@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/20 15:07:59 by rsabbah           #+#    #+#             */
/*   Updated: 2023/03/20 15:09:05 by rsabbah          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/**
 * @brief wait for the threads to finish.
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
		pthread_mutex_lock(&data->mtx_stop);
		data->stop = true;
		pthread_mutex_unlock(&data->mtx_stop);
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
int	philosophers(t_data *data)
{
	int	i;

	i = 0;
	data->t0 = timestamp();
	while (i < data->philo_nb)
	{
		if (pthread_create(&data->philo[i].th, NULL,
				philo_life, &data->philo[i]) != 0)
			return (thread_join(data, i), FAILURE);
		i++;
	}
	thread_join(data, i);
	return (SUCCESS);
}
