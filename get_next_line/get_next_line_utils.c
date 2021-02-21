/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: usavoia <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/11 19:02:45 by usavoia           #+#    #+#             */
/*   Updated: 2021/01/11 19:07:06 by usavoia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

size_t		ft_strlen(const char *s)
{
	size_t ret;

	if (!s)
		return (0);
	ret = 0;
	while (*s++)
		ret++;
	return (ret);
}

t_list		*ft_create_elem(int fd)
{
	t_list		*ret;

	if (!(ret = (t_list*)malloc(sizeof(t_list))))
		return (0);
	ret->fd = fd;
	ret->buf[0] = 0;
	ret->next = 0;
	return (ret);
}

t_list		*ft_add_list(t_list **head, int fd)
{
	t_list *temp;

	temp = ft_create_elem(fd);
	temp->next = *head;
	*head = temp;
	return (*head);
}

t_list		*find_fd(t_list **head, int fd)
{
	t_list	*temp;

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

int			resize(char **line, size_t len)
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
