/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rsabbah <rsabbah@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/16 11:17:38 by rsabbah           #+#    #+#             */
/*   Updated: 2023/03/20 10:47:00 by rsabbah          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	kill_all(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->philo_nb)
	{
		if (data->philo[i].pid != 0)
			kill(data->philo[i].pid, SIGKILL);
		i++;
	}
}

void	*check_full(void *arg)
{
	t_data	*data;
	int		i;

	data = (t_data *)arg;
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
		usleep(1000);
	}
	if (i == data->philo_nb)
		sem_post(data->stop);
	return (NULL);
}

int	main_monitor(t_data *data)
{
	pthread_t	th_check_full;

	if (pthread_create(&th_check_full, NULL, check_full, data) != 0)
	{
		kill_all(data);
		return (print_error(THREAD_ERR, NULL));
	}
	if (waitpid(-1, 0, WNOHANG) == 0)
		sem_wait(data->stop);
	kill_all(data);
	sem_post(data->count);
	pthread_join(th_check_full, NULL);
	return (SUCCESS);
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
			return (kill_all(data), FAILURE);
		if (data->philo[i].pid == 0)
			philo_life(&data->philo[i]);
		i++;
	}
	if (main_monitor(data) == FAILURE)
		return (FAILURE);
	return (SUCCESS);
}
