/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rsabbah <rsabbah@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/15 12:41:29 by rsabbah           #+#    #+#             */
/*   Updated: 2023/03/15 12:41:30 by rsabbah          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

int	ft_strcmp(const char *a, const char *b)
{
	int	i;

	i = 0;
	if (a == NULL || b == NULL)
		return (-1);
	while (a[i] && b[i] && a[i] == b[i])
		i++;
	return (a[i] - b[i]);
}
