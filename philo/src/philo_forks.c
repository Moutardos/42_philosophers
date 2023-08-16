/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_forks.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcozdenm <lcozdenm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/14 16:10:39 by lcozdenm          #+#    #+#             */
/*   Updated: 2023/08/14 18:58:04 by lcozdenm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"


int	take_forks(t_fork *l_fork, t_fork *r_fork)
{
	int	fail;

	fail = 0;
	pthread_mutex_lock(&l_fork->lock);
	pthread_mutex_lock(&r_fork->lock);
	if (!l_fork->is_used && !r_fork->is_used)
	{
		printf(" LOCK LFORK(%d) %d RFORK(%d) %d\n", l_fork->p_id, l_fork->is_used, r_fork->p_id, r_fork->is_used);
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

	l_fork = &philo->l_fork;
	r_fork = philo->r_fork;
	if (!l_fork->is_used && !r_fork->is_used)
		return (res = take_forks(l_fork, r_fork), printf(" LFORK %d RFORK %d;\n", philo->l_fork.is_used, philo->r_fork->is_used), res);
	return (1);
}

void	put_down_forks(t_philo *philo)
{
	t_fork	*l_fork;
	t_fork	*r_fork;

	l_fork = &philo->l_fork;
	r_fork = philo->r_fork;
	pthread_mutex_lock(&l_fork->lock);
	pthread_mutex_lock(&r_fork->lock);
	l_fork->is_used = FALSE;
	r_fork->is_used = FALSE;
	pthread_mutex_unlock(&l_fork->lock);
	pthread_mutex_unlock(&r_fork->lock);
}