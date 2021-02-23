/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: usavoia <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/22 12:51:26 by usavoia           #+#    #+#             */
/*   Updated: 2021/02/22 12:51:28 by usavoia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	print_prompt(void)
{
	char tmp[PATH_MAX];

	if (!errno)
		ft_putstr_fd(GRN"✓"NC, 1);
	else
		ft_putstr_fd(RED"𐄂"NC, 1);
	ft_putstr_fd(BGBLK" ", 1);
	ft_putstr_fd((get_value_env("USER"))->value, 1);
	ft_putstr_fd("@minishell"NC, 1);
	ft_putstr_fd(BGBLUEBLACK""NC, 1);
	ft_putstr_fd(BGBLUEBLACK, 1);
	ft_putstr_fd((getcwd(tmp, PATH_MAX)), 1);
	ft_putstr_fd(NC, 1);
	ft_putstr_fd(BLUE" "NC, 1);
}
