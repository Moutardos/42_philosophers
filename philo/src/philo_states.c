/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_states.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcozdenm <lcozdenm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/14 16:39:15 by lcozdenm          #+#    #+#             */
/*   Updated: 2023/09/30 15:56:22 by lcozdenm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	thinking(t_philo *philo)
{
	t_ms	to_wait;

	to_wait = philo->pinfo->tm_toeat;
	if (philo->pinfo->size % 2)
	{
		if (turn_to_wait_longer(philo))
		{
			to_wait = philo->pinfo->tm_toeat * 2;
		}
	}
	to_wait -= get_time(&philo->s_start);
	display_state(philo, THINKING);
	philo->state = EATING;
	usleep(min_death(philo, to_wait));
	reset_time(&philo->s_start);
}
// void	thinking(t_philo *philo)
// {
// 	t_ms	to_wait;

// 	if (philo->pinfo->size % 2 == 0)
// 		to_wait = philo->pinfo->tm_toeat;
// 	else
// 		to_wait = 0;
// 	display_state(philo, THINKING);
// 	philo->state = EATING;
// 	while (!stop_condition(philo) && get_time(&philo->s_start) < to_wait)
// 		usleep(100);
// 	reset_time(&philo->s_start);
// }

void	sleeping(t_philo *philo)
{
	t_ms	to_wait;

	display_state(philo, SLEEPING);
	philo->state = THINKING;
	to_wait = philo->pinfo->tm_tosleep;
	reset_time(&philo->s_start);
	usleep(to_wait);
}

void	eating(t_philo *philo)
{
	t_ms	to_wait;

	while (!stop_condition(philo) && use_forks(philo))
		usleep(100);
	if (stop_condition(philo))
		return ;
	display_state(philo, EATING);
	reset_time(&philo->last_meal);
	get_time(&philo->last_meal);
	to_wait = philo->pinfo->tm_toeat;
	usleep(to_wait);
	put_down_forks(philo);
	if (stop_condition(philo))
		return ;
	philo->state = SLEEPING;
	philo->eaten++;
	reset_time(&philo->s_start);
}

void	display_state(t_philo *philo, t_state state)
{
	t_ms	time;
	int		id;

	time = get_time(&philo->start) / 1000;
	id = philo->id;
	pthread_mutex_lock(&philo->pinfo->print_lock);
	if (state == THINKING)
		printf("%lu %d is thinking\n", time, id);
	else if (state == EATING)
	{
		printf("%lu %d has taken a fork\n", time, id);
		printf("%lu %d has taken a fork\n", time, id);
		printf("%lu %d is eating\n", time, id);
	}
	else if (state == SLEEPING)
		printf("%lu %d is sleeping\n", time, id);
	else if (state == TAKE_FORK)
	{
		printf("%lu %d has taken a fork\n", time, id);
	}
	else if (state == DEAD)
		printf("%lu %d died\n", philo->time_dead / 1000, id);
	pthread_mutex_unlock(&philo->pinfo->print_lock);
}

int	turn_to_wait_longer(t_philo *philo)
{
	int	start;
	int	gap;

	start = philo->id / 2;
	gap = (philo->pinfo->size + 1) / 2 - 1; 
	if (philo->eaten == start + gap * philo->waited)
	{
		philo->waited++;
		return (1);
	}
	return (0);
}
