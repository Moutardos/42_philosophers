/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcozdenm <lcozdenm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/23 09:07:10 by lcozdenm          #+#    #+#             */
/*   Updated: 2023/09/19 15:13:09 by lcozdenm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"
#include "philo.h"

int	main(int ac, const char **av)
{
	int			*args;
	int			i;
	pthread_t	*pdt;
	t_table		ptable;

	args = parse_args(ac, av);
	if (!args)
	{
		printf("./philosopher number_of_philosophers time_to_die time_to_eat");
		printf(" time_to_sleep [number_of_times_each_philosopher_must_eat]\n");
	}
	printf("\n");
	pdt = ft_calloc(args[0], sizeof(pthread_t));
	if (create_table(&ptable, args, ac - 1) == -1)
		return (safe_free(args), free_table(ptable), 0);
	i = -1;
	while (++i < args[0])
		pthread_create(&(pdt[i]), NULL, philo_life, &(ptable.philos[i]));
	start_routine(ptable.philos[0].pinfo);
	i = -1;
	while (++i < args[0])
		pthread_join(pdt[i], NULL);
	display_dead(ptable, pdt);
	return (safe_free(args), free_table(ptable), 0);
}
