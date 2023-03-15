/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_pause.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rsabbah <rsabbah@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/15 13:47:30 by rsabbah           #+#    #+#             */
/*   Updated: 2023/03/15 13:47:31 by rsabbah          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	process_pause(t_philo *philo, int time)
{
	int	start;

	(void)philo;
	start = timestamp();
	while (timestamp() - start < time)
		usleep(1000);
}
