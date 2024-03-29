/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcozdenm <lcozdenm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/03 11:08:41 by lcozdenm          #+#    #+#             */
/*   Updated: 2023/09/30 16:54:13 by lcozdenm         ###   ########.fr       */
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
	int				n_toeat;
	int				size;
	t_bool			stop;
	t_time			real_start;
	pthread_mutex_t	stop_lock;
	pthread_mutex_t	print_lock;
}	t_pinfo;

typedef struct s_philo
{
	int				id;
	pthread_t		th;
	t_fork			*l_fork;
	t_fork			*r_fork;
	t_bool			can_eat;
	t_state			state;
	t_time			start;
	t_ms			delay;
	t_time			idle_time;
	t_time			last_meal;
	t_ms			time_dead;
	t_pinfo			*pinfo;
	int				eaten;
	int				waited;
}	t_philo;

// Initialisation

t_philo	init_philo(int n, t_pinfo *pinfo);
t_philo	*create_table(int *args, int ac);
t_pinfo	*set_pinfo(int *args, int ac);
void	free_table(t_philo *philos);
void	start_routine(t_pinfo	*pinfo);

// Forks related

t_fork	*create_fork(void);
int		are_forks_free(t_fork *l_fork, t_fork *r_fork);
int		use_forks(t_philo *philo);
void	put_down_forks(t_philo *philo);

// States treatment

void	thinking(t_philo *philo);
void	sleeping(t_philo *philo);
void	eating(t_philo *philo);
void	display_state(t_philo *philo, t_state state);
int		turn_to_wait_longer(t_philo *philo);
// The daily life of a philosopher

int		treat_state(t_philo *philo);
void	*philo_life(void *data);
int		stop_condition(t_philo *philo);

/* Return the lowest time between t1 and the time left for philo to live*/
t_ms	min_death(t_philo *philo, t_ms t1);

void	display_dead(t_philo *philos, int size);

#endif