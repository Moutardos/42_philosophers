/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbru_fd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcozdenm <lcozdenm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/15 17:34:44 by lcozdenm          #+#    #+#             */
/*   Updated: 2023/03/23 09:29:52 by lcozdenm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "notlibft.h"

int	ft_putnbru_fd(unsigned int n, int fd)
{
	if (n > 9)
		return (ft_putnbr_fd(n / 10, fd) + ft_putnbr_fd(n % 10, fd));
	else
		return (ft_putchar_fd('0' + n, fd));
}
