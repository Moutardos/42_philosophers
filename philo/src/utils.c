/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcozdenm <lcozdenm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/23 09:55:53 by lcozdenm          #+#    #+#             */
/*   Updated: 2023/09/30 15:55:45 by lcozdenm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

int	*parse_args(int ac, const char **av)
{
	int	*args;
	int	i;

	i = 0;
	if (ac < 5 || ac > 6)
		return (NULL);
	ac -= 1;
	args = ft_sstrtoi(av + 1, &ac);
	if (!args)
		return (NULL);
	while (i < ac)
	{
		if (args[i] < 0)
			return (safe_free(args), NULL);
		i++;
	}
	return (args);
}

t_ms	get_time(t_time *start)
{
	t_time	now;
	t_ms	time;

	if (start->tv_sec == 0 && start->tv_usec == 0)
	{
		gettimeofday(start, NULL);
		now = *start;
	}
	else
		gettimeofday(&now, NULL);
	time = (now.tv_sec - start->tv_sec) * 1000000;
	time += now.tv_usec - start->tv_usec;
	return (time);
}

void	reset_time(t_time *start)
{
	start->tv_sec = 0;
	start->tv_usec = 0;
}

void	safe_free(void *ptr)
{
	if (ptr)
	{
		free(ptr);
		ptr = NULL;
	}
}
