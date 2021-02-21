/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: usavoia <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/11 14:35:14 by usavoia           #+#    #+#             */
/*   Updated: 2021/01/11 14:35:16 by usavoia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	char		*temp;
	const char	*s;

	if (!dest && !src)
		return (0);
	s = src;
	temp = dest;
	while (n--)
		*temp++ = *s++;
	return (dest);
}
