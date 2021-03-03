/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: usavoia <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/11 19:01:02 by usavoia           #+#    #+#             */
/*   Updated: 2021/01/15 18:40:56 by usavoia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

void	remove_buf(t_list_gnl **head, int fd)
{
	t_list_gnl *prev;
	t_list_gnl *curr;

	prev = *head;
	if (prev->fd == fd)
	{
		curr = prev->next;
		free(prev);
		*head = curr;
		return ;
	}
	while (prev->next->fd != fd)
		prev = prev->next;
	curr = prev->next;
	prev->next = curr->next;
	free(curr);
}

int		copy_buf_and_save_rest(t_list_gnl *found, char **line)
{
	size_t	i;
	size_t	j;
	int		ret;

	i = ft_stlen(*line);
	if (!resize(&(*line), i))
		return (12);
	ret = 0;
	j = 0;
	while (found->buf[j])
	{
		(*line)[i++] = found->buf[j];
		if (found->buf[j++] == '\n')
		{
			i--;
			ret = 1;
			break ;
		}
	}
	(*line)[i] = 0;
	i = 0;
	while (found->buf[j])
		found->buf[i++] = found->buf[j++];
	found->buf[i] = 0;
	return (ret);
}

int		error(char **line)
{
	free(*line);
	*line = 0;
	return (-1);
}

int		get_next_line(int fd, char **line)
{
	static t_list_gnl	*head;
	t_list_gnl			*found;
	int					size;
	int					rest;

	if (BUFFER_SIZE <= 0 || !line || (fd < 0)
			|| !(found = find_fd(&head, fd)))
		return (-1);
	*line = 0;
	if ((rest = copy_buf_and_save_rest(found, &(*line))))
		return (rest);
	while ((size = read(fd, found->buf, BUFFER_SIZE)) > 0 && size != -1)
	{
		found->buf[size] = 0;
		if ((rest = copy_buf_and_save_rest(found, &(*line))))
			return (rest);
	}
	remove_buf(&head, fd);
	if (size == -1)
		return (error(line));
	return (size);
}
