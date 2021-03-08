/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_exec2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cromaldeusavoia <marvin@42.fr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/08 13:10:12 by cromalde          #+#    #+#             */
/*   Updated: 2021/03/08 13:29:07 by cromaldeusa      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static int	condition(char *input, int i)
{
	return (!ft_memcmp("<", &(input[i]), 1) ||
		!ft_memcmp(">>", &(input[i]), 2) || (!ft_memcmp(">", &(input[i]), 1) &&
		ft_memcmp(">", &(input[i + 1]), 1)) || !ft_memcmp("|", &(input[i]), 1));
}

char		*ft_sgomitata_support(char *input, int num, int i, int j)
{
	char	*new;

	new = malloc(i + (num * 2) + 1);
	i = 0;
	while (input[i])
		if (condition(input, i))
		{
			if (!ft_memcmp(">>", &(input[i]), 2))
			{
				new[j++] = ' ';
				new[j++] = input[i++];
				new[j++] = input[i++];
				new[j++] = ' ';
			}
			else
			{
				new[j++] = ' ';
				new[j++] = input[i++];
				new[j++] = ' ';
			}
		}
		else
			new[j++] = input[i++];
	new[j] = 0;
	return (new);
}
