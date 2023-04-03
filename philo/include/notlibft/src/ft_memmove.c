/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcozdenm <lcozdenm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/21 17:33:35 by lcozdenm          #+#    #+#             */
/*   Updated: 2023/03/23 09:29:52 by lcozdenm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "notlibft.h"

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	unsigned char	*mem_dst;
	unsigned char	*mem_src;
	size_t			i;

	if ((dst == NULL) && (src == NULL))
		return (NULL);
	if (dst <= src)
		return (ft_memcpy(dst, src, len));
	mem_src = (unsigned char *) src;
	mem_dst = (unsigned char *) dst;
	i = 0;
	while (i < len)
	{
		mem_dst[len - i - 1] = mem_src[len - i - 1];
		i++;
	}
	return (dst);
}
