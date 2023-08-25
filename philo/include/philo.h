/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcozdenm <lcozdenm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/03 11:08:41 by lcozdenm          #+#    #+#             */
/*   Updated: 2023/08/25 14:55:42 by lcozdenm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include "utils.h"

typedef struct s_fork
{
	int				p_id;
	pthread_mutex_t	lock;
	t_bool			is_used;
}	t_fork;

typedef enum e_state
{
	THINKING,
	EATING,
	SLEEPING,
	TAKE_FORK,
	OUT,
	DEAD
}	t_state;

typedef struct s_pinfo
{
	t_ms			tm_todie;
	t_ms			tm_toeat;
	t_ms			tm_tosleep;
	unsigned int	n_toeat;
	int				size_table;
	t_bool			*stop;
	pthread_mutex_t	stop_lock;
}	t_pinfo;

typedef struct s_philo
{
	int				id;
	t_bool			*stop;
	t_fork			*l_fork;
	t_fork			*r_fork;
	t_bool			can_eat;
	t_state			state;
	t_time			start;
	t_time			s_start;
	t_time			last_meal;
	t_ms			time_dead;
	t_pinfo			pinfo;
	int				eaten;
}	t_philo;

typedef struct s_table
{
	t_philo			*philos;
	unsigned int	size;
}	t_table;

// Main
int	check_loop(t_table table, pthread_t *pdt);

// Initialisation
t_philo	init_philo(int n, t_time start);
int		create_table(t_table *table, t_time start, int *args, int ac);
int		set_pinfo(t_pinfo *pinfo, int *args, int ac);
void	free_table(t_table table);

// Forks related
t_fork	*create_fork(void);
int		are_forks_free(t_fork *l_fork, t_fork *r_fork);
int		use_forks(t_philo *philo);
void	put_down_forks(t_philo *philo);

// States treatment
void	thinking(t_philo *philo);
void	sleeping(t_philo *philo);
void	eating(t_philo *philo);
void	display_state(t_ms time, int id, t_state state);

// The daily life of a philosopher
int		treat_state(t_philo *philo);
void	*philo_life(void *data);
int		philo_dead(t_philo *philo);

#endif