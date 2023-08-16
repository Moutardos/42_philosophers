/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_init.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcozdenm <lcozdenm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/03 11:24:51 by lcozdenm          #+#    #+#             */
/*   Updated: 2023/08/16 17:43:32 by lcozdenm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

t_philo	init_philo(int n, t_time start)
{
	t_philo	philo;

	philo.id = n;
	philo.r_fork = NULL;
	philo.state = THINKING;
	philo.start = start;
	philo.eaten = 0;
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

int	create_table(t_table *table, t_time start, int *args, int ac)
{
	unsigned int	i;
	t_pinfo			pinfo;
	unsigned int	size;

	size = args[0];
	pinfo = set_pinfo(args, ac);
	table->philos = ft_calloc(size, sizeof(t_philo) * size);
	if (!table->philos)
		return (-1);
	i = 0;
	while (i < size)
	{
		table->philos[i] = init_philo(i, start);
		table->philos[i].l_fork = create_fork();
		if (!table->philos[i].l_fork)
			return (table->size = i + 1, -1);
		if (i > 0)
			table->philos[i].r_fork = table->philos[i - 1].l_fork;
		table->philos[i].pinfo = pinfo;
		i++;
	}
	if (size > 1)
		table->philos[0].r_fork = table->philos[size - 1].l_fork;
	table->size = size;
	return (0);
}

void	free_table(t_table table)
{
	int	i;

	i = 0;
	if (table.philos)
	{
		while (i < table.size)
		{
			if (table.philos[i].l_fork)
			{
				pthread_mutex_destroy(&table.philos[i].l_fork->lock);
				safe_free(table.philos[i].l_fork);
			}
			i++;
		}
		safe_free(table.philos);
	}
}