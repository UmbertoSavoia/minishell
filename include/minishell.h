#ifndef MINISHELL_H
# define MINISHELL_H

# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <sys/errno.h>
# include <fcntl.h>
# include <sys/wait.h>
# include <signal.h>
# include <sys/stat.h>
# include <dirent.h>

# include "../libft/libft.h"
# include "../get_next_line/get_next_line_bonus.h"

typedef struct	s_env
{
	char			*key;
	char			*value;
	struct s_env	*next;
}				t_env;

typedef struct	s_shell
{
	t_env	*envp;
}				t_shell;

extern t_shell		g_shell;

// ENV
void	init_env(char **env);
void	ft_push_front_env(t_env **head, t_env *new);
t_env	*ft_create_node_env(const char *env);

// UTILS
char	*get_key_env(const char *env, int *len_value);

#endif
