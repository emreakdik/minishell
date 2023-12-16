/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emre <emre@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/22 16:17:18 by akaniber          #+#    #+#             */
/*   Updated: 2023/12/16 20:50:02 by emre             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "../libft/libft.h"

# define EXEC 0
# define HEREDOC 1
# define PIPE 2
# define GREAT 3
# define GREATER 4
# define LESS 5
# define STDINN 0
# define STDOUT 1
# define STDERR 2

typedef struct s_env
{
	char			*key;
	char			*value;
}					t_env;

typedef struct s_data
{
	char			*read_data;
}					t_data;

typedef struct s_lexer
{
	t_list			*lex;
}					t_lexer;

typedef struct s_parse
{
	char			*cmd;
	char			**text;
	int				type;
	int				outfile;
	int				infile;
	int				fd;
	int				pid;
	int				control;
	int				std_in;
	struct s_parse	*next;
}					t_parse;

typedef struct s_shell
{
	t_list			*env;
	char			*cmd;
	t_lexer			*lex_list;
	t_parse			*parse;
	char			*heredoc;
	int				exec_status;
	char			*title;
}					t_shell;

extern int			g_does_have_heredoc;

/**
 * Lexer Functions
 */
void				lexer(t_shell *shell);
int					ignore_quote(char const *cmd, int i);

/**
 * Expander Functions
 */
int					check_quote(char *before, char *after);
int					is_count_odd(char *before, char c);
char				*get_env(t_list *env, char *key);
int					ft_ultimatestrcmp(char *key, char *tmp, int i, int *flag);
void				expand_question_mark(t_shell *shell, t_list *lex,
						char **temp, char *before);
void				expand_dollar_variable(t_shell *shell, t_list *lex,
						char **temp, char *before);
void				expander(t_shell *shell);
/**
 * Parser Functions
 */
void				mini_parse(t_list *lex, t_shell *m_shell, int a[3]);
void				flag_(t_parse *parse);
void				parse_text_m(t_parse *parse, char *str, int *j, int *flag);
void				tokenize_type_m(t_parse **parse, const char *str);
t_parse				*parse_init(size_t len);
int					ft_parser(t_shell *m_shell);
void				free_node(t_list *node);

/**
 * Execute Functions
 */
void				_free_env(t_list *tmp2, t_shell *m_shell);
void				free_env(t_shell *m_shell);
void				free_(t_shell *m_shell);
void				free_loop(int control, t_shell *m_shell);
void				execve_child_free(char **str, t_shell *m_shell);
void				free_text(char **text);
void				_free_parse(t_parse *parse);
void				free_parser(t_shell *m_shell);
int					*create_pipe(void);
void				run_command(char **env, t_parse *tmp, int *fd,
						t_shell *m_shell);
void				run_single_command(char **env, t_parse *parse,
						t_shell *m_shell);
void				multi_command_(t_parse *parse, char **env, t_shell *m_shell,
						int *fd);
void				multi_command(char **env, int x, t_parse *parse,
						t_shell *m_shell);
void				exec(char **env, t_shell *m_shell);
char				*search_command(char *cmd, char **value);
char				*_search_path(t_shell *m_shell);
void				search_path(t_parse *data, int i, t_shell *m_shell);
void				run_execve(t_parse *parse, char **env, int *fd,
						t_shell *m_shell);
void				exec_others(t_parse *parse, char **env, int *fd,
						t_shell *m_shell);
char				**get_args(t_parse *parse);
int					single_or_multi_command(t_shell *m_shell);
t_parse				*_next_command(t_parse **parse);

/**
 * Builtins Functions
 */
void				execute_builtin_command(t_parse *parse, t_shell *m_shell);
int					is_builtin(t_parse *data);
void				run_echo(t_parse *data, int *i);
void				exec_echo(t_parse *data, t_shell *m_shell);
void				print_list(void *data, t_shell *m_shell);
void				exec_env(t_shell *m_shell);
void				edit_env(t_list *node, char *key, char *value,
						t_shell *m_shell);
void				declare_export(void *data, t_shell *m_shell);
int					exec_export(t_parse *data, t_shell *m_shell);
int					unset_edit(t_list **node, t_list **prev_node,
						t_shell *m_shell);
void				exec_unset(t_parse *data, t_shell *m_shell, int i, int x);
void				change_old(char *str, t_shell *m_shell);
void				_change_pwd(t_env **env);
void				change_pwd(t_parse *data, t_shell *m_shell);
void				exec_cd1(char *str, t_parse *data, t_shell *m_shell);
void				exec_cd(t_parse *data, t_shell *m_shell);
void				edit_env_(t_list *node, char *key, char *value,
						t_shell *m_shell);
void				exec_pwd(t_parse *data, t_shell *m_shell);
char				*get_home(t_shell *m_shell);

/**
 * Signals Functions
 */
void				signals(int sig);
void				signals_control(void);

/**
 * Main Folder Functions
 */
void				error_free(t_list **node);
void				go_parser(t_shell *shell, char **env, int control);
void				get_readline(t_shell *shell);
void				shell_init(t_shell **shell);
void				env_get(char **env, t_shell **shell);
void				free_str(char **str);
void				get_title_from_env(t_shell **shell);

/**
 * Heredoc Folder Functions
 */
void				killer(int sig);
void				set_heredoc(int sig);
void				loop_heredoc(t_shell *m_shell);
void				heredoc(t_parse *parse, t_shell *m_shell);
void				get_input(t_parse *parse, int *fd);
void				get_var(int *fd, t_shell *m_shell);
char				*add_char(char *str, char a);

/**
 * Create Dup Folder Functions
 */
void				_create_dup(t_shell *m_shell);
void				create_dup(t_shell *m_shell, t_parse *parse);
void				create_dup_one(t_parse *parse, int *fd);
void				create_dup_two(t_parse *parse, int *fd);

/**
 * Check Folder Functions
 */
int					is_space(char *cmd);
int					print_error(void);
int					quote_check(char *data);
int					check(t_shell *shell);
int					quote_len1(char *data);
int					cmd_is_valid(t_lexer *lex_list, char *a, char *b);
int					is_valid_other(char *a, char *b);

/**
 * Utils Folder Functions
 */
void				_multi_command(t_parse **parse);
void				ft_newlstiter(t_list *lst, void (*f)(), t_shell *shell);
char				*ft_mini_strdup2(size_t len, char *s, int i,
						const char *str);
void				clear_pipe(int *fd);
void				wait_all(t_shell *m_shell);

/**
 * Create Files Folder Functions
 */
int					create_in_files_me(t_parse *parse);
int					create_files_m(t_shell *m_shell);
void				create_out_files_me(t_parse *m_parse, t_parse *prev_parse);
void				other_text_create_me(t_parse *m_parse);
void				other_out_filesme(t_parse *parse);
#endif
