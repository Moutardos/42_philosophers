/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bzero.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcozdenm <lcozdenm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/20 20:43:44 by lcozdenm          #+#    #+#             */
/*   Updated: 2023/03/23 09:29:52 by lcozdenm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "notlibft.h"

void	ft_bzero(void *s, size_t n)
{
	size_t			i;
	unsigned char	*mem_s;

	mem_s = (unsigned char *) s;
	i = 0;
	while (i < n)
	{
		mem_s[i] = 0;
		i++;
	}
}
