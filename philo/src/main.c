/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcozdenm <lcozdenm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/23 09:07:10 by lcozdenm          #+#    #+#             */
/*   Updated: 2023/04/16 02:26:43 by lcozdenm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"
#include "philo.h"

int	main(int ac,const char **av)
{
	int				*args;
	int	i;
	pthread_t		*pdt;
	t_table	ptable;
	t_time 	start = {0,0};

	printf("Time: %ld\n", get_time(&start));
	args = parse_args(ac, av);
	if (!args)
		return (1);
	printf("\n");
	printf("Time: %ld\n", get_time(&start));
	pdt = malloc(sizeof(pthread_t) * args[0]);
	if (create_table(&ptable, args[0], start, args, ac - 1) == -1)
		return (free(args), 0);
	i = 0;
	while (i < args[0])
	{
		pthread_create(&(pdt[i]), NULL, philo_life, &(ptable.philos[i]));
		pthread_join(pdt[i], NULL);
		i++;
	}
	free(args);
	return (0);
}