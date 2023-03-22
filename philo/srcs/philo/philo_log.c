/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_log.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rsabbah <rsabbah@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/22 13:51:25 by rsabbah           #+#    #+#             */
/*   Updated: 2023/03/22 13:51:42 by rsabbah          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	philo_log(t_philo *philo, char *log)
{
	pthread_mutex_lock(&philo->data->mtx_stop);
	if (philo->data->stop == false)
		print_log(log, philo);
	else
		philo->stop = true;
	pthread_mutex_unlock(&philo->data->mtx_stop);
}
