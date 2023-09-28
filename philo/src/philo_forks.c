/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_forks.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcozdenm <lcozdenm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/14 16:10:39 by lcozdenm          #+#    #+#             */
/*   Updated: 2023/09/28 21:46:35 by lcozdenm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

t_fork	*create_fork(void)
{
	t_fork	*fork;

	fork = malloc(sizeof(t_fork));
	if (!fork)
		return (NULL);
	if (pthread_mutex_init(&fork->lock, NULL))
	{
		return (safe_free(fork), NULL);
	}
	fork->is_used = FALSE;
	return (fork);
}

int	take_forks(t_fork *l_fork, t_fork *r_fork)
{
	pthread_mutex_lock(&l_fork->lock);
	if (!l_fork->is_used)
		l_fork->is_used = TRUE;
	else
	{
		pthread_mutex_unlock(&l_fork->lock);
		return (1);
	}
	pthread_mutex_unlock(&l_fork->lock);
	pthread_mutex_lock(&r_fork->lock);
	if (!r_fork->is_used)
	{
		r_fork->is_used = TRUE;
		pthread_mutex_unlock(&r_fork->lock);
	}
	else
	{
		pthread_mutex_unlock(&r_fork->lock);
		pthread_mutex_lock(&l_fork->lock);
		l_fork->is_used = FALSE;
		pthread_mutex_unlock(&l_fork->lock);
		return (1);
	}
	return (0);
}

int	use_forks(t_philo *philo)
{
	t_fork	*l_fork;
	t_fork	*r_fork;

	l_fork = philo->l_fork;
	r_fork = philo->r_fork;
	if (!r_fork)
		return (1);
	return (take_forks(l_fork, r_fork));
}

void	put_down_forks(t_philo *philo)
{
	t_fork	*l_fork;
	t_fork	*r_fork;

	l_fork = philo->l_fork;
	r_fork = philo->r_fork;
	pthread_mutex_lock(&l_fork->lock);
	l_fork->is_used = FALSE;
	pthread_mutex_unlock(&l_fork->lock);
	pthread_mutex_lock(&r_fork->lock);
	r_fork->is_used = FALSE;
	pthread_mutex_unlock(&r_fork->lock);
}
