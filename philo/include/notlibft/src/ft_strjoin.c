/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcozdenm <lcozdenm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/19 21:44:48 by lcozdenm          #+#    #+#             */
/*   Updated: 2023/03/23 09:29:52 by lcozdenm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "notlibft.h"

char	*ft_strjoin(const char *s1, const char *s2)
{
	char	*res;
	size_t	size_s1;
	size_t	size_s2;

	size_s1 = ft_strlen(s1);
	size_s2 = ft_strlen(s2);
	if (size_s1 + size_s2 >= SIZE_MAX)
		return (NULL);
	res = malloc(size_s1 + size_s2 + 1);
	if (res == NULL)
		return (NULL);
	res[0] = '\0';
	ft_strlcat(res, s1, size_s1 + 1);
	ft_strlcat(res, s2, size_s2 + size_s1 + 1);
	return (res);
}
