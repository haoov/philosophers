/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rsabbah <rsabbah@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/08 12:37:23 by rsabbah           #+#    #+#             */
/*   Updated: 2023/03/09 16:05:17 by rsabbah          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	clean_forks(t_data data)
{
	int	i;

	i = 0;

	while (i < data.philo_nb)
	{
		pthread_mutex_destroy(&data.forks[i]);
		i++;
	}
	free(data.forks);
}

void	cleanup(t_data data)
{
	if (data.philo)
		free(data.philo);
	if (data.forks)
		clean_forks(data);
	pthread_mutex_destroy(&data.mutex[LOG]);
	pthread_mutex_destroy(&data.mutex[END]);
	pthread_mutex_destroy(&data.mutex[COUNT]);
}
