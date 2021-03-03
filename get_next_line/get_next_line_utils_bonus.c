/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils_bonus.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: usavoia <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/11 19:02:16 by usavoia           #+#    #+#             */
/*   Updated: 2021/01/11 19:15:24 by usavoia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

size_t			ft_stlen(const char *s)
{
	size_t ret;

	if (!s)
		return (0);
	ret = 0;
	while (*s++)
		ret++;
	return (ret);
}

t_list_gnl		*ft_create_elem(int fd)
{
	t_list_gnl		*ret;

	if (!(ret = (t_list_gnl*)malloc(sizeof(t_list_gnl))))
		return (0);
	ret->fd = fd;
	ret->buf[0] = 0;
	ret->next = 0;
	return (ret);
}

t_list_gnl		*ft_add_list(t_list_gnl **head, int fd)
{
	t_list_gnl *temp;

	temp = ft_create_elem(fd);
	temp->next = *head;
	*head = temp;
	return (*head);
}

t_list_gnl		*find_fd(t_list_gnl **head, int fd)
{
	t_list_gnl	*temp;

	temp = *head;
	while (temp)
	{
		if (temp->fd == fd)
			break ;
		temp = temp->next;
	}
	if (!temp)
		return (ft_add_list(&(*head), fd));
	return (temp);
}

int				resize(char **line, size_t len)
{
	char	*new_line;
	size_t	i;

	if (!(new_line = (char*)malloc(len + BUFFER_SIZE + 1)))
		return (0);
	i = 0;
	while (i < len)
	{
		new_line[i] = (*line)[i];
		i++;
	}
	new_line[i] = 0;
	free(*line);
	*line = new_line;
	return (1);
}
