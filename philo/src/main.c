/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcozdenm <lcozdenm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/23 09:07:10 by lcozdenm          #+#    #+#             */
/*   Updated: 2023/04/03 13:49:22 by lcozdenm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"
#include "philo.h"

int	main(int ac,const char **av)
{
	int	*args;
	int	i;
	t_table	ptable;
	t_time start = {0,0};
	printf("Time: %ld\n", get_time(&start));
	// args = parse_args(ac, av);
	// if (!args)
	// 	return (1);
	// i = 0;
	// for (i = 0; i < ac - 1; i++)
	// 	printf("%d ", args[i]);
	printf("\n");
	printf("Time: %ld\n", get_time(&start));
	create_table(&ptable, 4);
	free(args);
	return (0);
}
