/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: usavoia <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/11 19:03:39 by usavoia           #+#    #+#             */
/*   Updated: 2021/01/11 19:10:52 by usavoia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <stdlib.h>
# include <unistd.h>

typedef struct	s_list
{
	int				fd;
	char			buf[BUFFER_SIZE + 1];
	struct s_list	*next;
}				t_list;

int				get_next_line(int fd, char **line);
t_list			*ft_create_elem(int fd);
t_list			*ft_add_list(t_list **head, int fd);
t_list			*find_fd(t_list **head, int fd);
int				resize(char **line, size_t len);
size_t			ft_strlen(const char *s);
int				copy_buf_and_save_rest(t_list *found, char **line);
void			remove_buf(t_list **head, int fd);
int				error(char **line);

#endif
