/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rsabbah <rsabbah@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/15 11:08:04 by rsabbah           #+#    #+#             */
/*   Updated: 2023/03/16 16:58:04 by rsabbah          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

static int	check_args(int argc, char **argv)
{
	int	i;

	if (argc < 5)
		return (print_error(ARGN_ERR, NULL));
	i = 1;
	while (i < argc)
	{
		if (only_digit(argv[i]) == false)
			return (print_error(ARG_ERR, argv[i]));
		i++;
	}
	return (SUCCESS);
}

static int	get_values(t_data *data, int argc, char **argv)
{
	if (check_args(argc, argv) == FAILURE)
		return (FAILURE);
	data->philo_nb = ft_atoi(argv[1]);
	if (data->philo_nb == 0 || data->philo_nb > 200)
		return (print_error(ARG_ERR, argv[1]));
	data->time.die = ft_atoi(argv[2]);
	data->time.eat = ft_atoi(argv[3]);
	data->time.sleep = ft_atoi(argv[4]);
	data->max_meal = -1;
	if (argc == 6)
	{
		data->max_meal = ft_atoi(argv[5]);
		if (data->max_meal < 1)
			return (print_error(ARG_ERR, argv[5]));
	}
	return (SUCCESS);
}

static void	init_philo(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->philo_nb)
	{
		pthread_mutex_init(&data->philo[i].infos, NULL);
		data->philo[i].id = i + 1;
		data->philo[i].data = data;
		i++;
	}
}

int	init_sem(t_data *data)
{
	sem_unlink(SEM_FORKS);
	sem_unlink(SEM_COUNT);
	sem_unlink(SEM_STOP);
	sem_unlink(SEM_PRINT);
	data->forks = sem_open(SEM_FORKS, O_CREAT, 0777, data->philo_nb);
	data->count = sem_open(SEM_COUNT, O_CREAT, 0777, 0);
	data->print = sem_open(SEM_PRINT, O_CREAT, 0777, 1);
	data->stop = sem_open(SEM_STOP, O_CREAT, 0777, 1);
	return (SUCCESS);
}

int	init(t_data *data, int argc, char **argv)
{
	memset(data, 0, sizeof (t_data));
	if (get_values(data, argc, argv) == FAILURE)
		return (FAILURE);
	data->philo = (t_philo *)ft_calloc(data->philo_nb, sizeof (t_philo));
	if (data->philo == NULL)
		return (print_error(MALLOC_ERR, "init.c:54"));
	if (init_sem(data) == FAILURE)
		return (FAILURE);
	if (data->forks == SEM_FAILED || data->count == SEM_FAILED)
		return (print_error(SEM_ERR, "init.c"));
	init_philo(data);
	return (SUCCESS);
}
