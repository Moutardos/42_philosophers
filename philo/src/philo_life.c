/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_life.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcozdenm <lcozdenm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/16 00:52:28 by lcozdenm          #+#    #+#             */
/*   Updated: 2023/09/21 16:12:45 by lcozdenm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*philo_life(void *data)
{
	t_philo	*philo;

	philo = ((t_philo *)data);
	while (philo->pinfo->stop)
		usleep(100);
	philo->start = philo->pinfo->real_start;
	get_time(&philo->last_meal);
	get_time(&philo->s_start);
	while (!treat_state(philo))
		usleep(100);
	return (NULL);
}

int	treat_state(t_philo *philo)
{
	if (stop_condition(philo))
		return (1);
	else if (philo->state == THINKING && !stop_condition(philo))
		thinking(philo);
	else if (philo->state == EATING && !stop_condition(philo))
		eating(philo);
	else if (philo->state == SLEEPING && !stop_condition(philo))
		sleeping(philo);
	return (stop_condition(philo));
}

int	stop_condition(t_philo *philo)
{
	int	goal_achieved;

	if (philo->pinfo->stop || philo->state == OUT)
		return (1);
	if (get_time(&philo->last_meal) >= philo->pinfo->tm_todie)
	{
		philo->state = DEAD;
		pthread_mutex_lock(&philo->pinfo->stop_lock);
		if (!philo->pinfo->stop)
			philo->pinfo->stop = TRUE;
		pthread_mutex_unlock(&philo->pinfo->stop_lock);
		philo->time_dead = get_time(&philo->start);
		return (1);
	}
	if (philo->pinfo->n_toeat >= 0)
	{
		if (philo->eaten >= philo->pinfo->n_toeat)
		{
			philo->state = OUT;
			return (1);
		}
	}
	return (0);
}

void	display_dead(t_table table)
{
	unsigned int	i;
	t_philo			current_philo;

	i = 0;
	while (i < table.size)
	{
		current_philo = table.philos[i];
		if (current_philo.state == DEAD)
			display_state(&current_philo, DEAD);
		i++;
	}
}
