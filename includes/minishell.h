/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yakdik <yakdik@student.42kocaeli.com.tr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/22 16:17:18 by akaniber          #+#    #+#             */
/*   Updated: 2023/11/30 19:38:49 by yakdik           ###   ########.fr       */
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
	char	*key;
	char	*value;
}			t_env;

typedef struct s_data
{
	char	*read_data;
}			t_data;

typedef struct s_lexer
{
	t_list	*lex;
}			t_lexer;

typedef struct s_parse
{
	char	*cmd;
	char	**text;
	int		type;
	int		outfile;
	int		infile;
	int		fd;
	int		pid;
	int		control;
}			t_parse;

typedef struct s_shell
{
	t_list	*env;
	char	*cmd;
	t_lexer	*lex_list;
	t_list	*parse;
	char	*heredoc;
	int		exec_status;
	char	*title;
}			t_shell;

typedef struct s_parse_params
{
	int		i;
	int		j;
	int		flag;
}			t_parse_params;

typedef struct s_fd_params
{
	int		*fd;
	int		fd_index;
}			t_fd_params;

extern int	g_does_have_heredoc;

int			count_of_quotes(char *before);
int			quote_index(char *str, int is_from_last);
void		remove_quotes(t_list *lex);
int			ft_ultimatestrcmp(char *key, char *tmp, int i, int *flag);
void		expand_dollar_variable(t_shell *shell, t_list *lex, char *temp);
void		expand_question_mark(t_shell *shell, t_list *lex, char *temp);
void		get_title_from_env(t_shell **shell);
char		*get_env(t_list *env, char *key);
t_parse		*parse_(int *j, t_list *new, int *i);
char		*after_dark2(char *key, char *tmp);
char		*quote_control(char *tmp);
char		*set_build(char *str);
char		*before_dollar(char *tmp);
char		*_search_path(t_shell *shell);
char		*get_home(t_shell *shell);
char		**get_args(t_parse *data, t_list *tmp);
char		*ft_strjoin2(char *s1, const char *s2);
int			ft_ultimatestrcmp(char *key, char *tmp, int i, int *flag);
int			quote_len1(char *data);
int			check(t_shell *shell);
int			is_builtin(t_list *tmp);
int			single_or_multi_command(t_shell *shell);
int			ft_parser(t_shell *shell);
int			create_files(t_shell *shell);
int			create_in_files(t_parse *data3, t_list *tmp3);
int			quote_check(char *data);
int			print_error(void);
int			is_space(char *cmd);
int			*create_pipe(void);
int			*create_pipe(void);
void		signals(int sig);
void		signals_control(void);
void		free_str1(char *str1, int flag);
void		free_tmps(char *str, char *str2, char *str_tmp);
void		_ft_exit_status(t_list *data, char *str1);
void		set_heredoc(int sig);
void		killer(int sig);
void		clear_pipe(int *fd);
void		env_get(char **env, t_shell **shell);
void		get_readline(t_shell *shell);
void		lexer(t_shell *shell);
void		expander(t_shell *shell);
void		print_list(t_shell *shell, void *data);
void		exec(t_shell *shell, char **env);
void		loop_heredoc(t_shell *shell);
void		run_single_command(t_shell *shell, char **env, t_list *data);
void		free_env(t_shell *shell);
void		free_parser(t_shell *shell);
void		free_loop(t_shell *shell, int control);
void		free_lexer(t_shell *shell);
void		free_text(char **text);
void		free_(t_shell *shell);
void		erase_after(char *tmp, t_list *data, int i);
void		free_tmp_tmp2(char *tmp, char *tmp1);
void		ft_tilde_build1(t_list *data, char *key, char *tmp);
void		ft_tilde_build2(t_list *data, char *str);
void		get_after_num(char *tmp, t_list *data, int i);
void		quote_build(char **tmp, char **data, int *i, int *j);
void		ft_exit_status(t_shell *shell, char *tmp, t_list *data);
void		free_node(t_list *node);
void		welcome_to_parse(t_shell *shell, t_list *node, t_parse_params arg);
void		get_text(t_parse **parse, char *str, int j, int a);
void		tokenize_type(t_parse **parse, const char *str);
void		free_parse(t_parse *parse);
void		parse_init(t_shell *shell);
void		does_dollar_make_sense(char *tmp, t_list *data, t_list *shell_data,
				int i);
void		_does_dollar_make_sense(t_env *y, char *before, char *after,
				t_list *data);
void		exec_echo(t_shell *shell, t_parse *data);
void		exec_env(t_shell *shell);
void		exec_export(t_shell *shell, t_parse *data);
void		exec_unset(t_shell *shell, t_parse *data);
void		exec_pwd(t_shell *shell, t_parse *data);
void		exec_cd(t_shell *shell, t_parse *data);
void		create_dup(t_shell *shell, t_list *data1, t_fd_params fd);
void		clear_pipe(int *fd);
void		switch_pipe(int **fd);
void		wait_all(t_shell *shell);
void		execute_builtin_command(t_shell *shell, t_list *tmp,
				t_fd_params fd);
void		exec_others(t_shell *shell, t_list *data, char **env,
				t_fd_params fd);
void		execve_child_free(t_shell *shell, char **str);
void		replace_data(t_list **data, char *tmp2);
void		ft_newlstiter(t_list *lst, void (*f)(), t_shell *shell);

#endif