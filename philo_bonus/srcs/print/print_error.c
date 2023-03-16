/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_error.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rsabbah <rsabbah@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/15 11:48:09 by rsabbah           #+#    #+#             */
/*   Updated: 2023/03/15 11:48:10 by rsabbah          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

int	print_error(char *error, char *infos)
{
	write(2, "philo: ", 7);
	write(2, error, ft_strlen(error));
	if (infos)
	{
		write(2, ": ", 2);
		write(2, infos, ft_strlen(infos));
	}
	write(2, "\n", 1);
	if (!ft_strcmp(error, ARG_ERR) || !ft_strcmp(error, ARGN_ERR))
		write(2, "try 'philo --help' for more informations\n", 41);
	return (FAILURE);
}
