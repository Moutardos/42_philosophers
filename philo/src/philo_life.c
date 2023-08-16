/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_life.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcozdenm <lcozdenm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/16 00:52:28 by lcozdenm          #+#    #+#             */
/*   Updated: 2023/08/16 17:43:45 by lcozdenm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*philo_life(void *data)
{
	t_philo	philo;

	philo = *((t_philo *)data);
	reset_time(&philo.s_start);
	reset_time(&philo.last_meal);
	get_time(&philo.last_meal);
	get_time(&philo.s_start);
	while (!treat_state(&philo) && philo.eaten < philo.pinfo.n_toeat)
		;
	return (NULL);
}

int	treat_state(t_philo *philo)
{
	t_state	new_state;

	if (philo->state == THINKING && !philo_dead(philo))
		thinking(philo);
	else if (philo->state == EATING && !philo_dead(philo))
		eating(philo);
	else if (philo->state == SLEEPING && !philo_dead(philo))
		sleeping(philo);
	if (philo_dead(philo))
		return (1);
	return (reset_time(&philo->s_start), 0);
}

int	philo_dead(t_philo *philo)
{
	int		id;
	t_ms	time;
	
	id = philo->id;
	if (philo->state == DEAD)
		return (1);
	if (get_time(&philo->last_meal) >= philo->pinfo.tm_todie)
	{
		time = get_time(&philo->start);
		philo->state = DEAD;
		display_state(time, philo->id, DEAD);
		return (1);
	}
	return (0);
}