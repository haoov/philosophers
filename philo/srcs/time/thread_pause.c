/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread_pause.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rsabbah <rsabbah@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/08 18:57:20 by rsabbah           #+#    #+#             */
/*   Updated: 2023/03/09 16:03:50 by rsabbah          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	thread_pause(t_philo *philo, int time)
{
	int	start;

	start = timestamp();
	while (philo->sig == CONTINUE && timestamp() - start < time)
	{
		usleep(500);
		check(philo, DEATH + SIGSTOP);
	}
}
