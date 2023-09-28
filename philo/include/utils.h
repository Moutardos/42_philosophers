/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcozdenm <lcozdenm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/23 09:56:15 by lcozdenm          #+#    #+#             */
/*   Updated: 2023/09/29 01:07:57 by lcozdenm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_H
# define UTILS_H

# define FALSE 0
# define TRUE 1
# include <sys/time.h>
# include <time.h>
# include <stdio.h>
# include <stdlib.h>
# include <limits.h>
# include <unistd.h>

typedef long unsigned int	t_ms;
typedef struct timeval		t_time;
typedef int					t_bool;

int		*parse_args(int ac, const char **av);

/* Return the time in ms of how much time elapsed between when start was 
   created and now.
   Using the function while start is set at 0 will set start at current time*/
t_ms	get_time(t_time *start);

/* Set the time in start at 0*/
void	reset_time(t_time *start);

/* Turn a string of number separated by spaces into an array of int.
	return null if met with an invalid number. */
int		*ft_sstrtoi(const char **str, int *size);

/* Check if the ptr is not null before freeing */
void	safe_free(void *ptr);
#endif