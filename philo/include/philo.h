/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcozdenm <lcozdenm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/03 11:08:41 by lcozdenm          #+#    #+#             */
/*   Updated: 2023/08/11 20:39:12 by lcozdenm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include "utils.h"

// Plutot que d'attendre (freeze le processus) quand la fourchette
// est prise on va modifier le bool is_used quand le droit est accorde

typedef struct s_fork
{
	pthread_mutex_t	lock;
	t_bool	is_used;
}	t_fork;

typedef enum e_state
{
	THINKING,
	EATING,
	SLEEPING,
	DEAD
}	t_state;

typedef struct s_pinfo
{
	t_ms			tm_todie;
	t_ms			tm_toeat;
	t_ms			tm_tosleep;
	unsigned int	n_toeat;
}	t_pinfo;

typedef struct s_philo
{
	int			id;
	t_fork		l_fork;
	t_fork		*r_fork;
	t_bool		can_eat;
	t_state		state;
	t_time		start;
	t_time		s_start;
	t_time		last_meal;
	t_pinfo		pinfo;
	int			eaten;
}	t_philo;

typedef struct s_table
{
	t_philo			*philos;
	unsigned int	size;
}	t_table;

// Initialisation
t_philo	init_philo(int n, t_time start);
int		create_table(t_table *table, t_time start, int *args, int ac);
t_pinfo	set_pinfo(int *args, int ac);
void	free_table(t_table table);

// Treatment
int		treat_state(t_philo *philo);
void	*philo_life(void *data);
int		philo_dead(t_philo *philo);
void	display_state(t_philo philo);
int		are_forks_free(t_fork *l_fork, t_fork *r_fork);
int		use_fork(t_fork *fork, t_bool use);
#endif