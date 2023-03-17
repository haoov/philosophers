/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread_pause.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rsabbah <rsabbah@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/08 18:57:20 by rsabbah           #+#    #+#             */
/*   Updated: 2023/03/17 10:28:02 by rsabbah          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	thread_pause(t_philo *philo, int time)
{
	int	start;

	start = timestamp();
	while (philo->stop == false && timestamp() - start < time)
	{
		usleep(1000);
		check(philo, STOP);
	}
}
