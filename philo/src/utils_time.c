/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcozdenm <lcozdenm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/11 18:29:55 by lcozdenm          #+#    #+#             */
/*   Updated: 2023/08/11 18:30:04 by lcozdenm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

t_ms get_time(t_time *start)
{
	t_time now;

	if (start->tv_sec == 0 && start->tv_usec == 0)
	{
		gettimeofday(start, NULL);
		now = *start;
	}
	else
		gettimeofday(&now, NULL);
	return ((now.tv_sec - start->tv_sec) * 1000000 + now.tv_usec - start->tv_usec);
}

void	reset_time(t_time *start)
{
	start->tv_sec = 0;
	start->tv_usec = 0;
}