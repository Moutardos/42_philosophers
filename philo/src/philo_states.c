/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_states.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcozdenm <lcozdenm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/14 16:39:15 by lcozdenm          #+#    #+#             */
/*   Updated: 2023/08/16 18:13:57 by lcozdenm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"


void	thinking(t_philo *philo)
{
	t_ms	to_wait; 

	if (philo->pinfo.tm_toeat < philo->pinfo.tm_tosleep)
			to_wait = philo->pinfo.tm_toeat;
		else
			to_wait = philo->pinfo.tm_tosleep;
	display_state(get_time(&philo->start) / 1000, philo->id, THINKING);
	philo->state = EATING;
	while (!philo_dead(philo) && get_time(&philo->s_start) < to_wait)
		;
}

void	sleeping(t_philo *philo)
{
	display_state(get_time(&philo->start) / 1000, philo->id, SLEEPING);
	philo->state = THINKING;
	while (!philo_dead(philo) && get_time(&philo->s_start) < philo->pinfo.tm_tosleep)
		;
}

void	eating(t_philo *philo)
{
	t_ms	to_wait;

	if (!use_forks(philo))
	{
		display_state(get_time(&philo->start) / 1000, philo->id, TAKE_FORK);
		display_state(get_time(&philo->start) / 1000, philo->id, TAKE_FORK);
		display_state(get_time(&philo->start) / 1000, philo->id, EATING);
		while (!philo_dead(philo) && get_time(&philo->s_start) < philo->pinfo.tm_toeat)
			;
		if (philo_dead(philo))
			return ;
		put_down_forks(philo);
		philo->state = SLEEPING;
		reset_time(&philo->last_meal);
		philo->eaten++;
	}
}

void	display_state(t_ms time, int id, t_state state)
{
	if (state == THINKING)
		printf("%lu %d is thinking\n", time, id);
	else if (state == EATING)
		printf("%lu %d is eating\n", time, id);
	else if (state == SLEEPING)
		printf("%lu %d is sleeping\n", time, id);
	else if (state == TAKE_FORK)
		printf("%lu %d has taken a fork\n", time, id);
	else if (state == DEAD)
		printf("%lu %d is dead\n", time, id);		
}