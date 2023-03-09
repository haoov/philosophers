/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_log.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rsabbah <rsabbah@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/08 14:54:42 by rsabbah           #+#    #+#             */
/*   Updated: 2023/03/09 16:27:05 by rsabbah          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	print_log(char *log, t_philo *philo)
{
	int	time;

	pthread_mutex_lock(&philo->data->mutex[PRINT]);
	time = timestamp() - philo->data->t0;
	monitor(philo);
	if (philo->dead && philo->sig != STOP)
	{
		printf("%d %d %s\n", time, philo->id, DEATH_LOG);
		philo->sig = STOP;
	}
	if (philo->sig == CONTINUE)
		printf("%d %d %s\n", time, philo->id, log);
	pthread_mutex_unlock(&philo->data->mutex[PRINT]);

}
