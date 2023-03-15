/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rsabbah <rsabbah@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/15 11:06:36 by rsabbah           #+#    #+#             */
/*   Updated: 2023/03/15 16:57:01 by rsabbah          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

int	main(int argc, char **argv)
{
	t_data	data;

	if (argc == 2 && !ft_strcmp(argv[1], HELP))
		return (print_helper(), FAILURE);
	if (init(&data, argc, argv) == FAILURE)
		return (cleanup(&data), FAILURE);
	if (process(&data) == FAILURE)
		return (cleanup(&data), FAILURE);
	return (cleanup(&data), SUCCESS);
}
