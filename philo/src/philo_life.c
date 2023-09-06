/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_life.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcozdenm <lcozdenm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/16 00:52:28 by lcozdenm          #+#    #+#             */
/*   Updated: 2023/09/06 17:24:17 by lcozdenm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*philo_life(void *data)
{
	t_philo	*philo;

	philo = ((t_philo *)data);
	while (*philo->pinfo.stop)
		;
	philo->start = *philo->pinfo.real_start;
	reset_time(&philo->s_start);
	reset_time(&philo->last_meal);
	get_time(&philo->last_meal);
	get_time(&philo->s_start);
	reset_time(&philo->s_start);
	get_time(&philo->s_start);
	while (!treat_state(philo) && philo->eaten < philo->pinfo.n_toeat)
		;
	return (NULL);
}

int	treat_state(t_philo *philo)
{
	t_state	new_state;

	if (philo_dead(philo))
		return (1);
	else if (philo->state == THINKING && !philo_dead(philo))
		thinking(philo);
	else if (philo->state == EATING && !philo_dead(philo))
		eating(philo);
	else if (philo->state == SLEEPING && !philo_dead(philo))
		sleeping(philo);
	return (reset_time(&philo->s_start), philo_dead(philo));
}

int	philo_dead(t_philo *philo)
{
	int		id;
	t_ms	time;
	
	id = philo->id;
	if (philo->state == DEAD || *(philo->pinfo.stop))
		return (1);
	//printf(" DEBUG PHILO  %d: LAST MEAL %d\n", philo->id, get_time(&philo->last_meal) / 1000);
	if (get_time(&philo->last_meal) >= philo->pinfo.tm_todie)
	{
		philo->time_dead = get_time(&philo->start) / 1000;
		pthread_mutex_lock(&philo->pinfo.stop_lock);
		if (!*philo->pinfo.stop)
			philo->state = DEAD;
		else
			philo->state = OUT;
		*philo->pinfo.stop = TRUE;
		pthread_mutex_unlock(&philo->pinfo.stop_lock);
		return (1);
	}
	return (0);
}