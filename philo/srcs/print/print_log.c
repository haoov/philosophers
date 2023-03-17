/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_log.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rsabbah <rsabbah@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/08 14:54:42 by rsabbah           #+#    #+#             */
/*   Updated: 2023/03/17 10:29:29 by rsabbah          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	print_log(char *log, t_philo *philo, t_signal sig)
{
	int	time;

	pthread_mutex_lock(&philo->data->mutex[LOG]);
	time = timestamp() - philo->data->t0;
	check(philo, SIGSTOP);
	if (philo->stop == false || sig == FPRINT)
		printf("%d %d %s\n", time, philo->id, log);
	pthread_mutex_unlock(&philo->data->mutex[LOG]);
}
