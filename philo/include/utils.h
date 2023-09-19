/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcozdenm <lcozdenm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/23 09:56:15 by lcozdenm          #+#    #+#             */
/*   Updated: 2023/09/13 15:23:34 by lcozdenm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_H
# define UTILS_H

# include "notlibft/notlibft.h"
# include <sys/time.h>

typedef long unsigned int	t_ms;
typedef struct timeval		t_time;

int		*parse_args(int ac, const char **av);

/* Return the time in ms of how much time elapsed between when start was 
   created and now.
   Using the function while start is set at 0 will set start at current time*/
t_ms	get_time(t_time *start);

/* Set the time in start at 0*/
void	reset_time(t_time *start);

#endif