/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcozdenm <lcozdenm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/21 01:40:44 by lcozdenm          #+#    #+#             */
/*   Updated: 2023/03/23 09:29:52 by lcozdenm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "notlibft.h"

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	unsigned char	*mem_s1;
	unsigned char	*mem_s2;

	if (n == 0)
		return (0);
	mem_s1 = (unsigned char *) s1;
	mem_s2 = (unsigned char *) s2;
	while ((n - 1))
	{
		if (*mem_s1 != *mem_s2)
			break ;
		n--;
		mem_s1++;
		mem_s2++;
	}
	return (*mem_s1 - *mem_s2);
}
