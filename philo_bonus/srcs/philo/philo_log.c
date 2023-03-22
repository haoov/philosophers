/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_log.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rsabbah <rsabbah@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/22 11:17:04 by rsabbah           #+#    #+#             */
/*   Updated: 2023/03/22 11:17:05 by rsabbah          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	philo_log(t_philo *philo, char *log)
{
	sem_wait(philo->data->stop);
	pthread_mutex_lock(&philo->infos);
	if (philo->stop == false)
		print_log(log, philo);
	pthread_mutex_unlock(&philo->infos);
	sem_post(philo->data->stop);
}
