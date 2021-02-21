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

# define RED "\x1b[31m"
# define BLACK "\x1b[30m"
# define BLUE "\x1b[34m"
# define NC "\033[0m"
# define BGBLK "\x1b[40m"
# define BGBLUE "\x1b[44m"

typedef struct	s_env
{
	char			*key;
	char			*value;
	struct s_env	*next;
}				t_env;

typedef struct	s_shell
{
	t_env			*envp;
	unsigned char	exit_code;
}				t_shell;

extern t_shell		g_shell;

/* ENV */
void	init_env(char **env);
void	ft_push_front_env(t_env **head, t_env *new);
t_env	*ft_create_node_env(const char *env);

/* SHLVL */
void	set_shlvl(void);

/* SIGNAL */
void	ft_sigquit(int sig);
void	ft_sigint(int sig);

/* PROMPT */
void	print_prompt(void);

/* UTILS */
char	*get_key_env(const char *env, int *len_value);
t_env	*get_value_env(char *key);
void	env_clear(void);


#endif
