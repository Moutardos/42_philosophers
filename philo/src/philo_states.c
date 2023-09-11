/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_states.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcozdenm <lcozdenm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/14 16:39:15 by lcozdenm          #+#    #+#             */
/*   Updated: 2023/09/11 16:03:18 by lcozdenm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"


void	thinking(t_philo *philo)
{
	t_ms	to_wait; 

	to_wait = 10;
	display_state(philo, THINKING);
	philo->state = EATING;
	while (!stop_condition(philo) && get_time(&philo->s_start) < to_wait);
		usleep(100);
}

void	sleeping(t_philo *philo)
{
	display_state(philo, SLEEPING);
	philo->state = THINKING;
	while (!stop_condition(philo) && get_time(&philo->s_start) < philo->pinfo->tm_tosleep)
		usleep(100);
}

void	eating(t_philo *philo)
{
	t_ms	to_wait;

	if (!use_forks(philo))
	{
		display_state(philo, TAKE_FORK);
		display_state(philo, EATING);
		reset_time(&philo->last_meal);
		get_time(&philo->last_meal);
		while (!stop_condition(philo) && get_time(&philo->s_start) < philo->pinfo->tm_toeat)
			usleep(100);
		put_down_forks(philo);
		if (stop_condition(philo))
			return ;
		philo->state = SLEEPING;
		philo->eaten++;
	}
}

void	display_state(t_philo *philo, t_state state)
{
	t_ms	time;
	int		id;

	time = get_time(&philo->start) / 1000;
	id = philo->id;
	pthread_mutex_lock(&philo->pinfo->printf_lock);
	if (state == THINKING)
		printf("%lu %d is thinking\n", time, id);
	else if (state == EATING)
		printf("%lu %d is eating\n", time, id);
	else if (state == SLEEPING)
		printf("%lu %d is sleeping\n", time, id);
	else if (state == TAKE_FORK)
	{
		printf("%lu %d has taken a fork\n", time, id);
		printf("%lu %d has taken a fork\n", time, id);
	}
	else if (state == DEAD)
		printf("%lu %d is dead\n", philo->time_dead / 1000, id);
	pthread_mutex_unlock(&philo->pinfo->printf_lock);
}