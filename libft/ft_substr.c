/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: usavoia <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/11 14:43:53 by usavoia           #+#    #+#             */
/*   Updated: 2021/01/11 14:57:53 by usavoia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char *ret;

	if (!s || ft_strlen(s) <= start || !len)
		return (ft_strdup(""));
	if (!(ret = malloc(++len)))
		return (0);
	ft_strlcpy(ret, &s[start], len);
	return (ret);
}
