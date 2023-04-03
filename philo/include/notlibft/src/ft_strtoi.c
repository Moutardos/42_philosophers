/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtoi.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcozdenm <lcozdenm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/27 18:43:43 by lcozdenm          #+#    #+#             */
/*   Updated: 2023/03/26 18:30:54 by lcozdenm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "notlibft.h"

// if (ft_isdigit(str[i]) != !(i == 0 && str[i] == '-'))
// return (0);
static int	ft_is_numeric(const char *str)
{
	unsigned int	i;

	i = 0;
	while (str[i])
	{
		if (!ft_isdigit(str[i]) && !(i == 0 && str[i] == '-'))
			return (0);
		i++;
	}
	return (1);
}

int	*ft_strtoi(const char **str, int *size)
{
	int				*res;
	unsigned int	len;
	unsigned int	i;

	if (!str)
		return (NULL);
	len = -1;
	if (size != NULL)
	{
		while (str[++len])
			if (!ft_is_numeric(str[len]))
				return (NULL);
		*size = len;
	}
	else
		len = *size;
	res = malloc(sizeof(int) * len);
	i = -1;
	while (res && ++i < len)
	{
		if (ft_strtoll(str[i]) > INT_MAX || ft_strtoll(str[i]) < INT_MIN)
			return (free(res), NULL);
		res[i] = ft_atoi(str[i]);
	}
	return (res);
}
