/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rsabbah <rsabbah@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/08 13:07:23 by rsabbah           #+#    #+#             */
/*   Updated: 2023/03/08 13:23:47 by rsabbah          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*ft_calloc(int nb, int size)
{
	void	*ptr;

	ptr = malloc(nb * size);
	if (ptr == NULL)
		return (NULL);
	memset(ptr, 0, nb * size);
	return (ptr);
}
