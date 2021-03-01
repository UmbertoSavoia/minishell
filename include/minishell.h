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
# include <string.h>
# include <limits.h>

# include "../libft/libft.h"
# include "../get_next_line/get_next_line_bonus.h"

# define RED "\x1b[31m"
# define BLACK "\x1b[30m"
# define BLUE "\x1b[34m"
# define GRN "\x1b[32m"
# define NC "\033[0m"
# define BGBLK "\x1b[40m"
# define BGBLUE "\x1b[44m"
# define BGBLUEBLACK "\x1b[44m\x1b[30m"
# define BGBLKGRN "\x1b[40m\x1b[32m"
# define BGBLKRED "\x1b[40m\x1b[31m"

# define DISPARI 1
# define PARI 0

typedef struct	s_env
{
	char			*key;
	char			*value;
	struct s_env	*next;
}				t_env;

typedef struct	s_shell
{
	t_env			*envp;
	t_env			*var_list;
	int				exit_code;
	char			**c_table;
	t_list			**table_list;
	char			*user;
	char			**envp_real;
	int				pid;
}				t_shell;

extern t_shell		g_shell;

/* ENV */
void	init_env(char **env);
void	ft_push_front_env(t_env **head, t_env *new);
t_env	*ft_create_node_env(const char *env);
t_env	*get_value_env(char *key);

/* REMOVE_ENV*/
void	env_lstdelone(t_env *lst, void (*del)(void*));
int		remove_t_env(t_env **head, void *data, int (*cmp)(const void*, const void*, size_t),
	void (*del)(void*));


/* SHLVL */
void	set_shlvl(void);

/* SIGNAL */
void	ft_sigquit(int sig);
void	ft_sigint(int sig);
void	ft_sigint_2(int sig);

/* PROMPT */
void	print_prompt(void);

/* PARSE EXEC */
void	parse_exec(void);
void	exec_commands(void);

/* FIND */
char	find_redir(int i);
char	find_builtin(int i, int *unused);
char	find_command(int i);

/* BUILT_INT */
void	built_pwd(void);
int		built_env(int i);

void	built_echo(int i);

void	built_unset(int i);

int		zero_to_space(int i, char c);
void	built_cd(int i);
void	built_exit(void);

void	built_export(int i);
void	add_env_list(int i);
int		print_export(void);
void	add_env_full(int i);

int		built_set(void);

void	built_dollar(int i, char **node, int *freeable);

/* VAR */
int		add_var_list(int i, char c);
char	var_search(t_list *head, char c, char *(*f)(const char*, int));

/* EXEC */
int		findexec(int i);
char	*get_path_command(t_list *node, int *found);

void	relative_path(int i);

/* REDIR */
void	redir_maj(t_list *node, char *sign, int flag);
char	**ft_list_to_arr_delim(t_list *start, t_list *end);
int		check_error_syntax_redir(t_list *node, char *sign);
void	redir_min(t_list *node, char *sign);

/* UTILS */
char	*get_key_env(const char *env, int *len_value);
void	env_clear(t_env *head);
t_list	*ft_split_get_token(char *table, char c);
t_list	**ft_split_list(char **table, char c);
char	echo_chaos_handler(char *k, char *v, int *i, char *s);

char	list_search(t_list *head, char *str, int (*f)(const void*, const void*, size_t));
char	relative_search(t_list *head, char *str, int (*f)(const void*, const void*, size_t));
void	clear_table_list(void);
int		check_quote(char *line);
char	ft_free(void *data);

t_env	*get_value_set(char *key);
t_env	*node_dup(t_env *node);
void	ft_free_arr(char **arr);
char	**ft_list_to_arr(int i);
//void	skip_quote(char **str);
void	skip_quote(char *str);

#endif
