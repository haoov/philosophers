/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rsabbah <rsabbah@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/08 10:37:35 by rsabbah           #+#    #+#             */
/*   Updated: 2023/03/09 16:43:10 by rsabbah          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	check_args(int argc, char **argv)
{
	int	i;

	if (argc < 5)
		return (print_error(ARGN_ERR, NULL), FAILURE);
	i = 1;
	while (i < argc)
	{
		if (only_digit(argv[i]) == false)
			return (print_error(ARG_ERR, argv[i]), FAILURE);
		i++;
	}
	return (SUCCESS);
}

static int	get_values(t_data *data, int argc, char **argv)
{
	if (check_args(argc, argv) == FAILURE)
		return (FAILURE);
	data->philo_nb = ft_atoi(argv[1]);
	if (data->philo_nb == 0)
		return (print_error(ARG_ERR, argv[1]), FAILURE);
	data->time.die = ft_atoi(argv[2]);
	data->time.eat = ft_atoi(argv[3]);
	data->time.sleep = ft_atoi(argv[4]);
	data->max_meal = -1;
	if (argc == 6)
	{
		data->max_meal = ft_atoi(argv[5]);
		if (data->max_meal < 1)
			return (print_error(ARG_ERR, argv[5]), FAILURE);
	}
	return (SUCCESS);
}

static void	init_philo(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->philo_nb)
	{
		pthread_mutex_init(&data->forks[i], NULL);
		pthread_mutex_init(&data->philo[i].infos, NULL);
		data->philo[i].id = i + 1;
		data->philo[i].r_fork = i;
		if (i == 0)
			data->philo[i].l_fork = data->philo_nb - 1;
		else
			data->philo[i].l_fork = i - 1;
		data->philo[i].time.die = data->time.die;
		data->philo[i].time.eat = data->time.eat;
		data->philo[i].time.sleep = data->time.sleep;
		data->philo[i].data = data;
		i++;
	}
}

int	init(t_data *data, int argc, char **argv)
{
	memset(data, 0, sizeof (t_data));
	data->t0 = timestamp();
	if (get_values(data, argc, argv) == FAILURE)
		return (FAILURE);
	data->philo = (t_philo *)ft_calloc(data->philo_nb, sizeof (t_philo));
	if (data->philo == NULL)
		return (print_error(MALLOC_ERR, "init.c:54"), FAILURE);
	data->forks = (pthread_mutex_t *)ft_calloc(data->philo_nb,
			sizeof (pthread_mutex_t));
	if (data->forks == NULL)
		return (print_error(MALLOC_ERR, "init.c:57"), FAILURE);
	pthread_mutex_init(&data->mutex[LOG], NULL);
	pthread_mutex_init(&data->mutex[COUNT], NULL);
	pthread_mutex_init(&data->mutex[END], NULL);
	init_philo(data);
	return (SUCCESS);
}
