/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcozdenm <lcozdenm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/23 09:56:15 by lcozdenm          #+#    #+#             */
/*   Updated: 2023/04/03 12:38:20 by lcozdenm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_H
# define UTILS_H

# include "notlibft/notlibft.h"
# include <sys/time.h>

typedef long int t_ms;
typedef struct timeval t_time;

int	*parse_args(int ac,const char **av);

/* return the time in ms since the start of the program */
t_ms get_time(t_time *start);
#endif