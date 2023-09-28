/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_parsing.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcozdenm <lcozdenm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/28 17:45:06 by lcozdenm          #+#    #+#             */
/*   Updated: 2023/09/29 00:30:58 by lcozdenm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

static int	ft_is_numeric(const char *str)
{
	unsigned int	i;

	i = 0;
	while (str[i])
	{
		if (!(str[i] >= '0' && str[i] <= '9') && !(i == 0 && str[i] == '-'))
			return (0);
		i++;
	}
	return (1);
}

static int	ft_isspace(int c)
{
	if (c == ' ')
		return (1);
	return (c == '\f' || c == '\n' || c == '\r' || c == '\t' || c == '\v');
}

static int	ft_atoi(const char *nptr)
{
	int		res;
	int		sign;
	size_t	i;

	res = 0;
	i = 0;
	sign = 1;
	while (nptr[i] && ft_isspace(nptr[i]))
		i++;
	if (nptr[i] && (nptr[i] == '-' || nptr[i] == '+'))
	{
		if (nptr[i] == '-')
			sign *= -1;
		i++;
	}
	while (nptr[i] && (nptr[i] >= '0' && nptr[i] <= '9'))
	{
		res *= 10;
		res += (nptr[i] - '0') * sign;
		i++;
	}
	return (res);
}

static long long	ft_strtoll(const char *nptr)
{
	long long	res;
	int			sign;
	size_t		i;

	res = 0;
	i = 0;
	sign = 1;
	while (nptr[i] && ft_isspace(nptr[i]))
		i++;
	if (nptr[i] && (nptr[i] == '-' || nptr[i] == '+'))
	{
		if (nptr[i] == '-')
			sign *= -1;
		i++;
	}
	while (nptr[i] && (nptr[i] >= '0' && nptr[i] <= '9'))
	{
		res *= 10;
		res += (nptr[i] - '0') * sign;
		i++;
	}
	return (res);
}

int	*ft_sstrtoi(const char **str, int *size)
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
