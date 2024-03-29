/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rsabbah <rsabbah@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/08 12:37:23 by rsabbah           #+#    #+#             */
/*   Updated: 2023/03/20 15:41:01 by rsabbah          ###   ########.fr       */
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

void	clean_philo(t_data data)
{
	int	i;

	i = 0;
	while (i < data.philo_nb)
	{
		pthread_mutex_destroy(&data.philo[i].infos);
		i++;
	}
	free(data.philo);
}

void	cleanup(t_data data)
{
	if (data.philo)
		clean_philo(data);
	if (data.forks)
		clean_forks(data);
	pthread_mutex_destroy(&data.mtx_stop);
	pthread_mutex_destroy(&data.mtx_count);
}
