/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: usavoia <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/11 14:28:26 by usavoia           #+#    #+#             */
/*   Updated: 2021/01/11 14:49:53 by usavoia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		len_num(int n)
{
	int cifre;

	cifre = 0;
	if (n == 0)
		return (1);
	while (n)
	{
		cifre++;
		n /= 10;
	}
	return (cifre);
}

char	*ft_itoa(int n)
{
	int					cifre;
	char				*ret;
	unsigned int		u_n;

	cifre = len_num(n);
	if (n < 0)
	{
		u_n = -(unsigned int)n;
		cifre++;
	}
	else
		u_n = n;
	if (!(ret = (char*)malloc(cifre + 1)))
		return (0);
	ret[cifre] = 0;
	if (n < 0)
		ret[0] = '-';
	ret[--cifre] = (u_n % 10) + '0';
	while (u_n /= 10)
		ret[--cifre] = (u_n % 10) + '0';
	return (ret);
}
