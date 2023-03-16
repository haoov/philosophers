/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rsabbah <rsabbah@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/15 11:54:55 by rsabbah           #+#    #+#             */
/*   Updated: 2023/03/16 16:10:55 by rsabbah          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	clean_philo(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->philo_nb)
	{
		pthread_mutex_destroy(&data->philo[i].infos);
		i++;
	}
	free(data->philo);
	data->philo = NULL;
}

void	cleanup(t_data *data)
{
	if (data->philo)
		clean_philo(data);
	sem_close(data->forks);
	sem_close(data->print);
	sem_close(data->count);
	sem_close(data->stop);
	sem_unlink(SEM_FORKS);
	sem_unlink(SEM_COUNT);
	sem_unlink(SEM_STOP);
	sem_unlink(SEM_PRINT);
}
