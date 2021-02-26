/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.h                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: usavoia <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/11 19:01:43 by usavoia           #+#    #+#             */
/*   Updated: 2021/01/11 19:14:41 by usavoia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_BONUS_H
# define GET_NEXT_LINE_BONUS_H

# include <stdlib.h>
# include <unistd.h>

# define BUFFER_SIZE 2048

typedef struct	s_list_gnl
{
	int					fd;
	char				buf[BUFFER_SIZE + 1];
	struct s_list_gnl	*next;
}				t_list_gnl;

int				get_next_line(int fd, char **line);
t_list_gnl		*ft_create_elem(int fd);
t_list_gnl		*ft_add_list(t_list_gnl **head, int fd);
t_list_gnl		*find_fd(t_list_gnl **head, int fd);
int				resize(char **line, size_t len);
size_t			ft_stlen(const char *s);
int				copy_buf_and_save_rest(t_list_gnl *found, char **line);
void			remove_buf(t_list_gnl **head, int fd);
int				error(char **line);

#endif
