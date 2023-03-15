/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_log.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rsabbah <rsabbah@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/15 11:50:18 by rsabbah           #+#    #+#             */
/*   Updated: 2023/03/15 18:58:17 by rsabbah          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	print_log(char *log, t_philo *philo)
{
	int	time;
	int	status;

	sem_wait(philo->data->print);
	time = timestamp() - philo->data->time.t0;
	waitpid(-1, &status, 0);
	if (WEXITSTATUS(status) != DEAD)
		printf("%d %d %s\n", time, philo->id, log);
	sem_post(philo->data->print);
}
