/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rsabbah <rsabbah@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/08 14:08:36 by rsabbah           #+#    #+#             */
/*   Updated: 2023/03/09 15:27:45 by rsabbah          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	thread_join(t_data *data, int th_nb)
{
	int	i;

	i = 0;
	while (i < th_nb)
	{
		pthread_join(data->philo[i].th, NULL);
		i++;
	}
}

int	threads(t_data *data)
{
	int	i;

	i = 0;
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
