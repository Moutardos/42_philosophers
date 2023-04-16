/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_life.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcozdenm <lcozdenm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/16 00:52:28 by lcozdenm          #+#    #+#             */
/*   Updated: 2023/04/16 02:31:51 by lcozdenm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*philo_life(void *data)
{
	t_philo	philo;

	philo = *((t_philo *)data);
	philo.s_start.tv_sec = 0;
	philo.s_start.tv_usec = 0;
	philo.last_meal.tv_sec = 0;
	philo.last_meal.tv_usec = 0;
	get_time(&philo.last_meal);
	get_time(&philo.s_start);
	while (get_time(&philo.last_meal) <= philo.pinfo.tm_todie)
	{
		treat_state(&philo);
	}
	printf("%lu philosophers %d  died\n",get_time(&philo.start), philo.id);
	return (NULL);
}

int	treat_state(t_philo *philo)
{
	t_ms	tm_tothink;

	if (philo->pinfo.tm_toeat < philo->pinfo.tm_tosleep)
		tm_tothink = philo->pinfo.tm_tosleep;
	else
		tm_tothink = philo->pinfo.tm_toeat;
	if (philo->state == THINKING)
	{
		printf("%lu philosopher %d  is thinking\n",get_time(&philo->start), philo->id);
		while (get_time(&philo->s_start) < tm_tothink && get_time(&philo->last_meal) < philo->pinfo.tm_todie)
			usleep(1);
		return (philo->state = EATING, 0);
	}
	if (philo->state == EATING)
	{
		printf("%lu philosopher %d  is eating\n",get_time(&philo->start), philo->id);
		while (get_time(&philo->s_start) < philo->pinfo.tm_toeat && (get_time(&philo->last_meal) < philo->pinfo.tm_todie))
			usleep(1);
		return (philo->state = SLEEPING, 0);
	}
	return (0);

}