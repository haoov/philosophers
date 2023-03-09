/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rsabbah <rsabbah@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/03 14:16:56 by rsabbah           #+#    #+#             */
/*   Updated: 2023/03/08 14:42:44 by rsabbah          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int argc, char **argv)
{
	t_data	data;

	if (argc == 2 && !ft_strcmp(argv[1], HELP))
		return (print_helper(), FAILURE);
	if (init(&data, argc, argv) == FAILURE)
		return (cleanup(data), FAILURE);
	if (threads(&data) == FAILURE)
		return (cleanup(data), FAILURE);
	return (cleanup(data), SUCCESS);
}
