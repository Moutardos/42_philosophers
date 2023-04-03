/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcozdenm <lcozdenm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/03 11:24:51 by lcozdenm          #+#    #+#             */
/*   Updated: 2023/04/03 13:53:13 by lcozdenm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

t_philo	init_philo(int n)
{
	t_philo	philo;

	philo.id = n;
	pthread_mutex_init(&philo.fork, NULL);
	philo.n_fork = NULL;
	philo.nb_forks = 0;
	philo.state = THINKING;
	philo.last_meal = 0;
	get_time(&philo.s_start);
	return (philo);
}

int	create_table(t_table *table, unsigned int size)
{
	unsigned int	i;

	table->philos = malloc(sizeof(t_philo) * size);
	if (!table->philos)
		return (-1);
	i = 0;
	while (i < size)
	{
		table->philos[i] = init_philo(i);
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

