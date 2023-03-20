/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rsabbah <rsabbah@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/16 11:17:38 by rsabbah           #+#    #+#             */
/*   Updated: 2023/03/20 18:08:24 by rsabbah          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	wait_all(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->philo_nb)
	{
		waitpid(-1, 0, 0);
		i++;
	}
}

void	check_full(t_data *data)
{
	int		i;

	i = 0;
	while (i < data->philo_nb)
	{
		if (waitpid(-1, 0, WNOHANG) > 0)
			break ;
		if (data->max_meal > 0)
		{
			sem_wait(data->count);
			i++;
		}
	}
	usleep(1000);
	if (i == data->philo_nb)
		sem_post(data->stop);
}

int	philo_start(t_data *data)
{
	int	i;

	i = 0;
	data->time.t0 = timestamp();
	sem_wait(data->stop);
	while (i < data->philo_nb)
	{
		data->philo[i].pid = fork();
		if (data->philo[i].pid == -1)
			return (wait_all(data), FAILURE);
		if (data->philo[i].pid == 0)
			philo_life(&data->philo[i]);
		i++;
	}
	check_full(data);
	wait_all(data);
	return (SUCCESS);
}
