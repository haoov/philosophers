/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rsabbah <rsabbah@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/08 13:01:25 by rsabbah           #+#    #+#             */
/*   Updated: 2023/03/08 13:01:37 by rsabbah          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

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
