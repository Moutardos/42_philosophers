/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_forks.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcozdenm <lcozdenm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/14 16:10:39 by lcozdenm          #+#    #+#             */
/*   Updated: 2023/08/18 17:26:36 by lcozdenm         ###   ########.fr       */
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
	int	fail;

	fail = 0;
	pthread_mutex_lock(&l_fork->lock);
	pthread_mutex_lock(&r_fork->lock);
	if (!l_fork->is_used && !r_fork->is_used)
	{
		l_fork->is_used = TRUE;
		r_fork->is_used = TRUE;
	}
	else
		fail = 1;
//	printf(" LFORK %d RFORK %d, NOW UNLOCK; RETURN %D\n", l_fork->is_used, r_fork->is_used, fail);
	pthread_mutex_unlock(&l_fork->lock);
	pthread_mutex_unlock(&r_fork->lock);
	return (fail);
}

int	use_forks(t_philo *philo)
{
	t_fork	*l_fork;
	t_fork	*r_fork;
	int		res;

	l_fork = philo->l_fork;
	r_fork = philo->r_fork;
	if (!r_fork)
		return (1);
	if (!l_fork->is_used && !r_fork->is_used)
		return (res = take_forks(l_fork, r_fork), res);
	return (1);
}

void	put_down_forks(t_philo *philo)
{
	t_fork	*l_fork;
	t_fork	*r_fork;

	l_fork = philo->l_fork;
	r_fork = philo->r_fork;
	pthread_mutex_lock(&l_fork->lock);
	pthread_mutex_lock(&r_fork->lock);
	l_fork->is_used = FALSE;
	r_fork->is_used = FALSE;
	pthread_mutex_unlock(&l_fork->lock);
	pthread_mutex_unlock(&r_fork->lock);
}