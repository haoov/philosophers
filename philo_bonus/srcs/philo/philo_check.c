/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_check.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rsabbah <rsabbah@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/22 11:01:37 by rsabbah           #+#    #+#             */
/*   Updated: 2023/03/22 13:12:38 by rsabbah          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	philo_check(t_philo *philo, bool *stop)
{
	pthread_mutex_lock(&philo->infos);
	if (philo->stop == true)
		*stop = true;
	pthread_mutex_unlock(&philo->infos);
}
