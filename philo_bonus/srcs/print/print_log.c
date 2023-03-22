/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_log.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rsabbah <rsabbah@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/15 11:50:18 by rsabbah           #+#    #+#             */
/*   Updated: 2023/03/22 11:29:45 by rsabbah          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	print_log(char *log, t_philo *philo)
{
	int		time;
	bool	stop;

	stop = false;
	time = timestamp() - philo->data->time.t0;
	if (stop == false)
		printf("%d %d %s\n", time, philo->id, log);
}
