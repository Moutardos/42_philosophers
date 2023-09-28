/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcozdenm <lcozdenm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/23 09:07:10 by lcozdenm          #+#    #+#             */
/*   Updated: 2023/09/29 00:42:30 by lcozdenm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"
#include "philo.h"

int	main(int ac, const char **av)
{
	int			*args;
	int			i;
	t_philo		*table;

	args = parse_args(ac, av);
	if (!args)
	{
		printf("./philosopher number_of_philosophers time_to_die time_to_eat");
		printf(" time_to_sleep [number_of_times_each_philosopher_must_eat]\n");
		return (1);
	}
	table = create_table(args, ac - 1);
	if (!table)
		return (safe_free(args), free_table(table), 0);
	i = -1;
	while (++i < args[0])
		pthread_create(&(table[i].th), NULL, philo_life, &(table[i]));
	i = -1;
	while (++i < args[0])
		pthread_join(table[i].th, NULL);
	display_dead(table, args[0]);
	return (safe_free(args), free_table(table), 0);
}
