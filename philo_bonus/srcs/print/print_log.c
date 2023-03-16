/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_log.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rsabbah <rsabbah@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/15 11:50:18 by rsabbah           #+#    #+#             */
/*   Updated: 2023/03/16 16:08:39 by rsabbah          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	print_log(char *log, t_philo *philo, t_signal sig)
{
	int	time;

	sem_wait(philo->data->print);
	time = timestamp() - philo->data->time.t0;
	printf("%d %d %s\n", time, philo->id, log);
	if (sig == UNLOCK)
		sem_post(philo->data->print);
}
