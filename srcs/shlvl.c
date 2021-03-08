/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shlvl.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cromaldeusavoia <marvin@42.fr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/08 13:20:45 by cromalde          #+#    #+#             */
/*   Updated: 2021/03/08 13:26:54 by cromaldeusa      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	set_shlvl(void)
{
	t_env	*tmp;
	int		num;

	tmp = get_value_env("SHLVL");
	num = ft_atoi(tmp->value) + 1;
	free(tmp->value);
	tmp->value = ft_itoa(num);
}
