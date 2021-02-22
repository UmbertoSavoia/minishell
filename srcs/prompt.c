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
	ft_putstr_fd(BGBLK" ", 1);
	ft_putstr_fd((get_value_env("USER"))->value, 1);
	ft_putstr_fd("@minishell"NC, 1);
	ft_putstr_fd(BGBLUE BLACK""NC, 1);
	ft_putstr_fd(BGBLUE BLACK, 1);
	ft_putstr_fd((get_value_env("PWD"))->value, 1);
	ft_putstr_fd(NC, 1);
	ft_putstr_fd(BLUE" "NC, 1);
}
