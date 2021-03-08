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
# include <termios.h>
# include <curses.h>

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
# define UP 2
# define DW 3

# define GVE get_value_env
# define GNC g_shell.table_list[i]->next->content

# define CTRL_KEY(k) ((k) & 0x1f)

typedef struct		s_path
{
	char			**path;
	DIR				*folder;
	size_t			lc;
	struct dirent	*entry;
	int				j;
	char			*tmp2;
	char			*ret;
}					t_path;

typedef struct		s_env
{
	char			*key;
	char			*value;
	struct s_env	*next;
}					t_env;

typedef struct		s_hist
{
	char			*content;
	struct s_hist	*prev;
	struct s_hist	*next;
}					t_hist;

typedef struct		s_shell
{
	t_env			*envp;
	t_env			*var_list;
	t_list			**table_list;
	t_hist			*history;
	int				hist_size;
	int				exit_code;
	char			**c_table;
	char			*user;
	char			**envp_real;
	int				pid;
	int				len_prompt;
	int				curs;
	struct termios	orig_termios;
	struct termios	raw;
	int				len_string;
	char			final_string[LINE_MAX];
}					t_shell;

extern t_shell		g_shell;

/*
** ENV **
*/
void				init_env(char **env);
void				ft_push_front_env(t_env **head, t_env *new);
t_env				*ft_create_node_env(const char *env);
t_env				*get_value_env(char *key);

/*
** REMOVE_ENV **
*/
int					env_lstdelone(t_env *lst, void (*del)(void*));
int					remove_t_env(t_env **head, void *data,
	int (*cmp)(const void*, const void*, size_t), void (*del)(void*));

/*
** SHLVL **
*/
void				set_shlvl(void);

/*
** SIGNAL **
*/
void				ft_sigquit(int sig);
void				ft_sigint(int sig);
void				ft_sigint_2(int sig);

/*
** PROMPT **
*/
void				print_prompt(void);

/*
** PARSE EXEC **
*/
void				parse_exec(void);
void				exec_commands(void);
char				*ft_sgomitata_support(char *input, int num, int i, int j);

/*
** FIND **
*/
char				find_redir(int i);
char				find_builtin(int i, int *unused);
char				find_command(int i);

/*
** BUILT_INT **
*/
void				built_pwd(void);
int					built_env(int i);

void				built_echo(int i);

void				built_unset(int i);

int					zero_to_space(int i, char c);
void				built_cd(int i);
void				built_exit(int i);
void				built_exit_code(t_list *value);

void				built_export(int i);
void				add_env_list(int i);
int					print_export(void);
void				add_env_full(int i);

int					built_set(void);

void				built_dollar(int i, char **node, int *freeable);

/*
** VAR **
*/
int					add_var_list(int i, char c);
char				var_search(t_list *head, char c,
	char *(*f)(const char*, int));

/*
** EXEC **
*/
int					findexec(int i);
char				*get_path_command(char *node, int *found);

/*
** REDIR **
*/
void				redir_maj(t_list *node, char *sign, int flag, int fd);
char				**ft_list_to_arr_delim(t_list *start, t_list *end);
int					check_error_syntax_redir(t_list *node, char *sign);
void				redir_min(t_list *node, char *sign, int fd);

/*
** PIPE **
*/
void				built_pipe(int i);
void				exec_pipe(int pip[][2], int j, int i);
void				pipe_close(int j, int pip[][2]);
void				multi_pipe_cicle(int *k, int j, int pip[][2], int i);
void				do_last_command(int pip[][2], int k, int i);
void				open_pipe(int j, int i);

/*
** HISTORY **
*/
t_hist				*ft_histnew(void *content);
int					ft_histadd_front(t_hist **lst, t_hist *new);
void				ft_hist_clear(t_hist **lst);

void				init_hist(void);
void				navigate_history(int dir);

/*
** UTILS **
*/
char				*get_key_env(const char *env, int *len_value);
t_list				*ft_split_get_token(char *table, char c);
t_list				**ft_split_list(char **table, char c);
char				echo_chaos_handler(char *k, char *v, int *i, char *s);
void				ft_lstremove_if_until(t_list **head, void *data,
			int (*cmp)(const void*, const void*, size_t), void (*del)(void*));

char				list_search(t_list *head, char *str,
						int (*f)(const void*, const void*, size_t));
void				clear_table_list(void);
int					check_quote(char *line);
char				ft_free(void *data);

t_env				*get_value_set(char *key);
t_env				*node_dup(t_env *node);
int					ft_free_arr(char **arr);
char				**ft_list_to_arr(int i);
void				skip_quote(char *str);

char				**ft_env_to_arr(void);
int					ft_envsize(t_env *lst);
void				env_clear(t_env *head);
void				calc_size(t_list *tmp, t_list *end, int *j);

/*
** TERMINAL **
*/
int					get_next_terminal(char **input);
void				disable_raw_mode(void);
int					termios_reset_mode(void);

void				print_error(int error);
int					ft_strrchr_mod(const char *s, const char *end, int c);
int					ft_strchr_mod(const char *s, const char *end, int c);
char				*escape_cursor_create(int pos, char *c);

int					process_keypress(char c);
char				editor_read_key(void);
void				enable_raw_mode(void);

int					key_del(void);
int					key_char(char c);
int					key_arrow(void);

void				ctrl_left(void);
void				ctrl_right(void);

void				insert_char_in_the_middle(char c);
int					key_char(char c);

#endif
