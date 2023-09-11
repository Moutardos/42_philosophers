/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_life.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcozdenm <lcozdenm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/16 00:52:28 by lcozdenm          #+#    #+#             */
/*   Updated: 2023/09/11 16:03:23 by lcozdenm         ###   ########.fr       */
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
	usleep(100);
	if (stop_condition(philo))
		return (1);
	else if (philo->state == THINKING && !stop_condition(philo))
		thinking(philo);
	else if (philo->state == EATING && !stop_condition(philo))
		eating(philo);
	else if (philo->state == SLEEPING && !stop_condition(philo))
		sleeping(philo);
	return (reset_time(&philo->s_start), stop_condition(philo));
}

int	stop_condition(t_philo *philo)
{
	int	goal_achieved;

	if (philo->pinfo->stop)
		return (1);
	if (get_time(&philo->last_meal) >= philo->pinfo->tm_todie)
	{
		philo->state = DEAD;
		philo->time_dead = get_time(&philo->start);
	}
	goal_achieved = FALSE;
	if (philo->pinfo->n_toeat >= 0)
		if (philo->eaten >= philo->pinfo->n_toeat)
			goal_achieved = TRUE;
	if (philo->state == DEAD || goal_achieved)
	{
		pthread_mutex_lock(&philo->pinfo->stop_lock);
		if (!philo->pinfo->stop)
			philo->pinfo->stop = TRUE;			
		pthread_mutex_unlock(&philo->pinfo->stop_lock);
		return (1);
	}
	return (0);
}