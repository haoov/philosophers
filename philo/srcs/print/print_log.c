/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_log.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rsabbah <rsabbah@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/08 14:54:42 by rsabbah           #+#    #+#             */
/*   Updated: 2023/03/20 15:23:03 by rsabbah          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	print_log(char *log, t_philo *philo)
{
	int	time;

	time = timestamp() - philo->data->t0;
	printf("%d %d %s\n", time, philo->id, log);
}
