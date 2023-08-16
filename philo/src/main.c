/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcozdenm <lcozdenm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/23 09:07:10 by lcozdenm          #+#    #+#             */
/*   Updated: 2023/08/14 18:51:23 by lcozdenm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"
#include "philo.h"

int	main(int ac,const char **av)
{
	int			*args;
	int			i;
	pthread_t	*pdt;
	t_table		ptable;
	t_time 		start = {0,0};

	printf("Time: %ld\n", get_time(&start));
	args = parse_args(ac, av);
	if (!args)
	{
		ft_printf("./philosopher number_of_philosophers time_to_die time_to_eat time_to_sleep [number_of_times_each_philosopher_must_eat]\n");
		return (1);
	}
	printf("\n");
	printf("Time: %ld\n", get_time(&start));
	pdt = ft_calloc(args[0], sizeof(pthread_t));
	if (create_table(&ptable, start, args, ac - 1) == -1)
		return (free(args), free_table(ptable), 0);
	i = -1;
	while (++i < args[0])
		pthread_create(&(pdt[i]), NULL, philo_life, &(ptable.philos[i]));
	i = -1;
	while (++i < args[0])
		pthread_join(pdt[i], NULL);
	safe_free(args);
	return (0);
}