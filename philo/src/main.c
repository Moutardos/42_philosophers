/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcozdenm <lcozdenm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/23 09:07:10 by lcozdenm          #+#    #+#             */
/*   Updated: 2023/09/06 17:03:18 by lcozdenm         ###   ########.fr       */
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
		return (safe_free(args), free_table(ptable), 0);
	i = -1;
	while (++i < args[0])
	{
		printf("   Philo ID %d : rfork : %p (originally %p)\n",i, ptable.philos[i].r_fork, ptable.philos[i > 0 ? i -1 : ptable.size - 1].l_fork);
	}
	i = -1;
	while (++i < args[0])
		pthread_create(&(pdt[i]), NULL, philo_life, &(ptable.philos[i]));
	i = -1;
	get_time(ptable.philos[0].pinfo.real_start);
	pthread_mutex_lock(&ptable.philos[0].pinfo.stop_lock);
	*ptable.philos[0].pinfo.stop = FALSE;
	pthread_mutex_unlock(&ptable.philos[0].pinfo.stop_lock);
	while (++i < args[0])
		pthread_join(pdt[i], NULL);
	check_loop(ptable, pdt);
	safe_free(args);
	free_table(ptable);
	return (0);
}

int	check_loop(t_table table, pthread_t *pdt)
{
	int		i;
	t_philo	current_philo;
	
	i = 0;
	while (i < table.size)
	{
		current_philo = table.philos[i];
		if (current_philo.state == DEAD)
		{
			if (current_philo.state == DEAD)
				display_state(current_philo.time_dead, current_philo.id, DEAD);
			return (0);
		}
		i++;
	}
	return (0);
}