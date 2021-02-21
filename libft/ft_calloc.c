/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: usavoia <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/11 14:25:57 by usavoia           #+#    #+#             */
/*   Updated: 2021/01/11 14:26:01 by usavoia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t num, size_t size)
{
	void	*ret;

	if (!(ret = malloc(num * size)))
		return (0);
	ft_bzero(ret, num * size);
	return (ret);
}
