/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_think.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rsabbah <rsabbah@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/22 10:59:43 by rsabbah           #+#    #+#             */
/*   Updated: 2023/03/22 14:21:12 by rsabbah          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	philo_think(t_philo *philo, bool *stop)
{
	int	i;

	i = 0;
	philo_log(philo, THINK_LOG);
	philo_wait(philo->data->time.think);
	while (i < 2)
	{
		sem_wait(philo->data->forks);
		philo_log(philo, FORK_LOG);
		if (philo->data->philo_nb == 1)
			philo_wait(philo->data->time.die);
		philo_check(philo, stop);
		if (*stop)
			return (philo_put_down_fork(philo, i));
		i++;
	}
}
