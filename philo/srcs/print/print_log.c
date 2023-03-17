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

/**
 * @brief print the given log message.
 * 
 * We use the LOG mutex so that only one thread can write at the same time.
 * We check if the data.stop value is not true, if its not or if we 
 * received the FPRINT (force print) signal we print the log.
 * 
 * @param log the log string.
 * @param philo a pointer to a struct containing the philo's data.
 * @param sig the print signal.
*/
void	print_log(char *log, t_philo *philo, t_signal sig)
{
	int	time;

	pthread_mutex_lock(&philo->data->mutex[LOG]);
	time = timestamp() - philo->data->t0;
	check(philo, STOP);
	if (philo->stop == false || sig == FPRINT)
		printf("%d %d %s\n", time, philo->id, log);
	pthread_mutex_unlock(&philo->data->mutex[LOG]);
}
