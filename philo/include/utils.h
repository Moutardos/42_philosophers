/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcozdenm <lcozdenm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/23 09:56:15 by lcozdenm          #+#    #+#             */
/*   Updated: 2023/04/21 11:42:30 by lcozdenm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_H
# define UTILS_H

# include "notlibft/notlibft.h"
# include <sys/time.h>

typedef long unsigned int t_ms;
typedef struct timeval t_time;

int	*parse_args(int ac,const char **av);

/* return the time in micro second since the start of the program */
t_ms get_time(t_time *start);

void	reset_time(t_time *start);
#endif