/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcozdenm <lcozdenm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/23 09:55:53 by lcozdenm          #+#    #+#             */
/*   Updated: 2023/03/23 10:16:18 by lcozdenm         ###   ########.fr       */
/*                 dd                                                           */
/* ************************************************************************** */

#include "utils.h"

int	*parse_args(int ac,const char **av)
{
	int	*args;
	int i;

	i = 0;
	if (ac < 5 || ac > 6)
		return (NULL);
	ac -= 1;
	args = ft_strtoi(av + 1, &ac);
	if (!args)
		return (NULL);
	while (i < ac)
	{
		if (args[i] < 0)
			return (free(args), NULL);
		i++;
	}
	return (args);
}