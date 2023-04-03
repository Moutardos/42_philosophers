/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcozdenm <lcozdenm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/03 11:08:41 by lcozdenm          #+#    #+#             */
/*   Updated: 2023/04/03 13:29:37 by lcozdenm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include "utils.h"

typedef pthread_mutex_t t_fork;

typedef enum e_state
{
	THINKING,
	EATING,
	SLEEPING,
	DEAD
}	t_state;

typedef struct s_philo
{
	int		id;
	t_fork	fork;
	t_fork	*n_fork;
	int		nb_forks;
	t_state	state;
	t_time	s_start;
	t_ms	last_meal;
}	t_philo;

typedef struct s_table
{
	t_philo			*philos;
	unsigned int	size;
}	t_table;

t_philo	init_philo(int n);
int		create_table(t_table *table, unsigned int size);

#endif