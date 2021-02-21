/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: usavoia <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/11 14:34:55 by usavoia           #+#    #+#             */
/*   Updated: 2021/01/11 14:53:17 by usavoia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_memcmp(const void *s1, const void *s2, size_t n)
{
	const unsigned char	*su1;
	const unsigned char	*su2;
	int					ret;

	su1 = s1;
	su2 = s2;
	ret = 0;
	while (0 < n)
	{
		if ((ret = *su1 - *su2) != 0)
			break ;
		su1++;
		su2++;
		n--;
	}
	return (ret);
}
