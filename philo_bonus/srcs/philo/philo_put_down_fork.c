/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_put_down_fork.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rsabbah <rsabbah@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/22 11:04:49 by rsabbah           #+#    #+#             */
/*   Updated: 2023/03/22 11:28:24 by rsabbah          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	philo_put_down_fork(t_philo *philo, int fork_nb)
{
	int	i;

	i = 0;
	while (i < fork_nb)
	{
		sem_post(philo->data->forks);
		i++;
	}
}
