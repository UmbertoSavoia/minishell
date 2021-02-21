/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: usavoia <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/11 14:37:57 by usavoia           #+#    #+#             */
/*   Updated: 2021/01/11 14:51:56 by usavoia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putnbr_fd(int n, int fd)
{
	unsigned int	u_n;
	char			s;

	if (n < 0)
	{
		u_n = -(unsigned int)n;
		write(fd, "-", 1);
	}
	else
		u_n = n;
	if (u_n < 10)
	{
		s = (u_n + '0');
		write(fd, &s, 1);
	}
	else
	{
		ft_putnbr_fd((u_n / 10), fd);
		ft_putnbr_fd((u_n % 10), fd);
	}
}
