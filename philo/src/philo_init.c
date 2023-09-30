/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_init.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcozdenm <lcozdenm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/03 11:24:51 by lcozdenm          #+#    #+#             */
/*   Updated: 2023/09/30 16:54:13 by lcozdenm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

t_philo	init_philo(int n, t_pinfo *pinfo)
{
	t_philo	philo;

	philo.id = n + 1;
	philo.r_fork = NULL;
	philo.delay = 0;
	if (philo.id % 2 == 0)
		philo.state = EATING;
	else
		philo.state = THINKING;
	philo.eaten = 0;
	philo.pinfo = pinfo;
	philo.waited = 0;
	philo.start = pinfo->real_start;
	reset_time(&philo.idle_time);
	reset_time(&philo.last_meal);
	return (philo);
}

t_pinfo	*set_pinfo(int *args, int ac)
{
	t_pinfo	*pinfo;

	pinfo = malloc(sizeof(t_pinfo));
	if (!pinfo)
		return (NULL);
	pinfo->stop = FALSE;
	if (pthread_mutex_init(&pinfo->stop_lock, NULL))
		return (safe_free(pinfo), NULL);
	if (pthread_mutex_init(&pinfo->print_lock, NULL))
	{
		pthread_mutex_destroy(&pinfo->stop_lock);
		return (safe_free(pinfo), NULL);
	}
	reset_time(&pinfo->real_start);
	get_time(&pinfo->real_start);
	pinfo->tm_todie = args[1] * 1000;
	pinfo->tm_toeat = args[2] * 1000;
	pinfo->tm_tosleep = args[3] * 1000;
	pinfo->n_toeat = -1;
	if (ac == 5)
		pinfo->n_toeat = args[4];
	pinfo->size = args[0];
	return (pinfo);
}

t_philo	*create_table(int *args, int ac)
{
	int		i;
	t_pinfo	*pinfo;
	t_philo	*philos;

	pinfo = set_pinfo(args, ac);
	if (!pinfo)
		return (NULL);
	philos = malloc(pinfo->size * sizeof(t_philo));
	if (!philos)
		return (NULL);
	i = 0;
	while (i < pinfo->size)
	{
		philos[i] = init_philo(i, pinfo);
		philos[i].l_fork = create_fork();
		if (!philos[i].l_fork)
			return (free_table(philos), NULL);
		if (i > 0)
			philos[i].r_fork = philos[i - 1].l_fork;
		i++;
	}
	if (pinfo->size > 1)
		philos[0].r_fork = philos[pinfo->size - 1].l_fork;
	return (philos);
}

void	free_table(t_philo *philos)
{
	int	i;

	i = 0;
	if (philos)
	{
		pthread_mutex_destroy(&philos[i].pinfo->print_lock);
		pthread_mutex_destroy(&philos[i].pinfo->stop_lock);
		while (i < philos[0].pinfo->size)
		{
			if (philos[i].l_fork)
			{
				pthread_mutex_destroy(&philos[i].l_fork->lock);
				safe_free(philos[i].l_fork);
			}
			i++;
		}
		safe_free(philos[0].pinfo);
		safe_free(philos);
	}
}
