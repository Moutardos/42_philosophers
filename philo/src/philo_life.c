/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_life.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcozdenm <lcozdenm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/16 00:52:28 by lcozdenm          #+#    #+#             */
/*   Updated: 2023/04/21 12:30:00 by lcozdenm         ###   ########.fr       */
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
	while (philo.state != DEAD)
	{
		if (philo_dead(&philo))
			return (NULL);
		treat_state(&philo);
	}
	return (NULL);
}

int	treat_state(t_philo *philo)
{
	t_ms	tm_towait;
	t_state	new_state;

	if (philo->state == THINKING && !philo_dead(philo))
	{
		if (philo->pinfo.tm_toeat < philo->pinfo.tm_tosleep)
			tm_towait = philo->pinfo.tm_tosleep;
		else
			tm_towait = philo->pinfo.tm_toeat;
		new_state = EATING;
	}
	else if (philo->state == EATING && !philo_dead(philo))
	{
		tm_towait = philo->pinfo.tm_toeat;
		new_state = SLEEPING;
		reset_time(&philo->last_meal);
	}
	else if (philo->state == SLEEPING && !philo_dead(philo))
	{
		tm_towait = philo->pinfo.tm_tosleep;
		new_state = THINKING;
	}
	display_state(*philo);
	while (!philo_dead(philo) && get_time(&philo->s_start) < tm_towait)
		;
	if (philo_dead(philo))
		return (1);
	return (philo->state = new_state, reset_time(&philo->s_start), 0);
}

void	display_state(t_philo philo)
{
	int		id;
	t_ms	time;

	time = get_time(&philo.start) / 1000;
	id = philo.id;
	if (philo.state == THINKING)
		printf("%lu philosopher %d is thinking\n", time, id);
	else if (philo.state == EATING)
		printf("%lu philosopher %d is eating\n", time, id);
	else if (philo.state == SLEEPING)
		printf("%lu philosopher %d is sleeping\n", time, id);
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
		printf("%lu philosopher %d is dead\n", time / 1000, id);
		display_state(*philo);
		return (1);
	}
	return (0);
}