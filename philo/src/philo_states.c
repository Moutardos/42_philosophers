/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_states.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcozdenm <lcozdenm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/14 16:39:15 by lcozdenm          #+#    #+#             */
/*   Updated: 2023/08/25 15:12:16 by lcozdenm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"


void	thinking(t_philo *philo)
{
	t_ms	to_wait; 

	to_wait = 0;
	display_state(get_time(&philo->start) / 1000, philo->id, THINKING);
	philo->state = EATING;
	// if (philo->pinfo.size_table % 2)
	// {
	// 	if (philo->pinfo.tm_toeat )
	// 		to_wait =  ((philo->id - 1) % 3) * philo->pinfo.tm_toeat;
	// }
	while (!philo_dead(philo) && get_time(&philo->s_start) < to_wait);
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
		reset_time(&philo->last_meal);
		get_time(&philo->last_meal);
		while (!philo_dead(philo) && get_time(&philo->s_start) < philo->pinfo.tm_toeat)
			;
		put_down_forks(philo);
		if (philo_dead(philo))
			return ;
		philo->state = SLEEPING;
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