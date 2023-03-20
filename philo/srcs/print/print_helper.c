/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_helper.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rsabbah <rsabbah@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/08 12:55:45 by rsabbah           #+#    #+#             */
/*   Updated: 2023/03/20 08:54:54 by rsabbah          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	print_helper(void)
{
	printf("PHILOSOPHERS\n\n");
	printf("A given number of philosophers are seating around a table.\n");
	printf("Each philosopher must eat, sleep and then think.\n");
	printf("If a philosopher do not eat for too long, he dies.\n");
	printf("The program displays each action of each philosopher.\n\n");
	printf("usage : ./philo [args..] [opt_arg]\n");
	printf("The philo cmd takes 4 arguments and 1 optional argument\n");
	printf("\targ1 : number of philosophers\n");
	printf("\targ2 : time to die. ");
	printf("Time it takes a philosopher to die (in ms)\n");
	printf("\targ3 : time to eat. ");
	printf("Time it takes a philosopher to eat (in ms)\n");
	printf("\targ4 : time to sleep. ");
	printf("Time it takes a philosophers to sleep (in ms)\n");
	printf("\topt_arg : number of time a philosopher must eat\n\n");
	printf("Errors :\n");
	printf("\tThere must be at least one philosopher at the table and ");
	printf("not more than 200\n");
	printf("\tPhilosophers must eat at least one time.\n");
}
