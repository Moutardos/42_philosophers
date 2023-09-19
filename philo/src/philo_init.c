/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_init.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcozdenm <lcozdenm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/03 11:24:51 by lcozdenm          #+#    #+#             */
/*   Updated: 2023/09/19 15:52:39 by lcozdenm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

t_philo	init_philo(int n)
{
	t_philo	philo;

	philo.id = n + 1;
	philo.r_fork = NULL;
	if (n % 2)
		philo.state = THINKING;
	else
		philo.state = EATING;
	philo.eaten = 0;
	reset_time(&philo.s_start);
	reset_time(&philo.last_meal);
	return (philo);
}

t_pinfo	*set_pinfo(int *args, int ac)
{
	t_pinfo	*pinfo;

	pinfo = malloc(sizeof(t_pinfo));
	if (!pinfo)
		return (NULL);
	pinfo->stop = TRUE;
	if (pthread_mutex_init(&pinfo->stop_lock, NULL))
		return (safe_free(pinfo), NULL);
	if (pthread_mutex_init(&pinfo->printf_lock, NULL))
	{
		pthread_mutex_destroy(&pinfo->stop_lock);
		return (safe_free(pinfo), NULL);
	}
	pinfo->real_start.tv_usec = 0;
	pinfo->real_start.tv_sec = 0;
	pinfo->tm_todie = args[1] * 1000;
	pinfo->tm_toeat = args[2] * 1000;
	pinfo->tm_tosleep = args[3] * 1000;
	pinfo->n_toeat = -1;
	if (ac == 5)
		pinfo->n_toeat = args[4];
	pinfo->size_table = args[0];
	return (pinfo);
}

int	create_table(t_table *table, int *args, int ac)
{
	unsigned int	i;
	t_pinfo			*pinfo;

	pinfo = set_pinfo(args, ac);
	if (!pinfo)
		return (-1);
	table->size = args[0];
	table->philos = ft_calloc(table->size, sizeof(t_philo));
	if (!table->philos)
		return (-1);
	i = 0;
	while (i < table->size)
	{
		table->philos[i] = init_philo(i);
		table->philos[i].l_fork = create_fork();
		if (!table->philos[i].l_fork)
			return (-1);
		if (i > 0)
			table->philos[i].r_fork = table->philos[i - 1].l_fork;
		table->philos[i].pinfo = pinfo;
		i++;
	}
	if (table->size > 1)
		table->philos[0].r_fork = table->philos[table->size - 1].l_fork;
	return (0);
}

void	free_table(t_table table)
{
	unsigned int	i;

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

void	start_routine(t_pinfo	*pinfo)
{
	get_time(&pinfo->real_start);
	pthread_mutex_lock(&pinfo->stop_lock);
	pinfo->stop = FALSE;
	pthread_mutex_unlock(&pinfo->stop_lock);
}
