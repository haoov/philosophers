/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rsabbah <rsabbah@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/15 12:07:29 by rsabbah           #+#    #+#             */
/*   Updated: 2023/03/15 18:53:13 by rsabbah          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

/* static int	kill_process(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->philo_nb)
	{
		printf("%d %d KILL\n", timestamp() - data->time.t0, i);
		kill(data->philo[i].pid, SIGKILL);
		i++;
	}
	return (SUCCESS);
}

static void	main_monitor(t_data *data)
{
	bool	stop;
	int		status;

	stop = false;
	while (stop == false)
	{
		waitpid(-1, &status, 0);
		if (WEXITSTATUS(status) == DEAD)
		{
			sem_wait(data->stop);
			kill_process(data);
			sem_post(data->stop);
			stop = true;
		}
	}
} */

static int	check_full(t_data *data)
{
	int	i;
	int	status;

	i = 0;
	data->full = fork();
	if (data->full == -1)
		return (print_error(FORK_ERR, "process.c:51"), FAILURE);
	if (data->full != 0)
		return (SUCCESS);
	while (i < data->philo_nb)
	{
		waitpid(-1, &status, 0);
		if (WEXITSTATUS(status) == DEAD)
			break ;
		sem_wait(data->count);
		i++;
	}
	if (i == data->philo_nb)
		return (FULL);
	return (FAILURE);
}

static void	process_wait(int p_nb)
{
	int	i;

	i = 0;
	while (i < p_nb)
	{
		waitpid(-1, NULL, 0);
		i++;
	}
}

int	process(t_data *data)
{
	int	i;

	i = 0;
	if (check_full(data) == FAILURE)
		return (FAILURE);
	data->time.t0 = timestamp();
	while (i < data->philo_nb)
	{
		data->philo[i].pid = fork();
		if (data->philo[i].pid == -1)
			return (process_wait(i), FAILURE);
		if (data->philo[i].pid == 0)
			philo_life(data, i);
		i++;
	}
	process_wait(i);
	return (SUCCESS);
}
