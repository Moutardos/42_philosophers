/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcozdenm <lcozdenm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/03 11:24:51 by lcozdenm          #+#    #+#             */
/*   Updated: 2023/04/21 12:19:25 by lcozdenm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

t_philo	init_philo(int n, t_time start)
{
	t_philo	philo;

	philo.id = n;
	pthread_mutex_init(&philo.fork.lock, NULL);
	philo.fork.is_used = FALSE;
	philo.n_fork = NULL;
	philo.state = THINKING;
	philo.start = start;
	return (philo);
}

t_pinfo	set_pinfo(int *args, int ac)
{
	t_pinfo	pinfo;

	pinfo.tm_todie = args[1] * 1000;
	pinfo.tm_toeat = args[2] * 1000;
	pinfo.tm_tosleep = args[3] * 1000;
	if (ac == 5)
		pinfo.n_toeat = args[4];
	return (pinfo);
}

int	create_table(t_table *table, unsigned int size, t_time start, int *args, int ac)
{
	unsigned int	i;
	t_pinfo			pinfo;

	pinfo = set_pinfo(args, ac);
	table->philos = malloc(sizeof(t_philo) * size);
	if (!table->philos)
		return (-1);
	i = 0;
	while (i < size)
	{
		table->philos[i] = init_philo(i, start);
		table->philos[i].pinfo = pinfo;
		i++;
	}
	i = 0;
	while (i < size)
	{
		if (i - 1 >= 0)
			table->philos[i].n_fork = &table->philos[i - 1].fork;
		else if (i == 0 && size > 1)
			table->philos[i].n_fork = &table->philos[size - 1].fork;
		i++;
	}
	table->size = size;
	return (0);
}