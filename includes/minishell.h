/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: enorie <enorie@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/29 14:28:30 by enorie            #+#    #+#             */
/*   Updated: 2024/03/23 12:39:12 by enorie           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "../libft/libft.h"
# include "./get_next_line.h"
# include <fcntl.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <signal.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/wait.h>
# include <unistd.h>

# define APPEND 1
# define TRUNC 2
# define USE_HEREDOC 3
# define USE_INFILE 4
# define ERROR_MALLOC -1

# define ERROR_MSG1 "error: syntax error near unexpected token '|'\n"
# define ERROR_MSG2 "error: syntax error near unexpected token 'newline'\n"
# define ERROR_MSG3 "error: syntax error near unexpected token '<<'\n"
# define ERROR_MSG4 "error: syntax error near unexpected token '<'\n"
# define ERROR_MSG5 "error: syntax error near unexpected token '>>'\n"
# define ERROR_MSG6 "error: syntax error near unexpected token '>'\n"

extern int			g_signal;

typedef struct s_file
{
	char			*file;
	int				mode;
	struct s_file	*next;
}					t_file;

typedef struct s_prompt
{
	t_file			*file;
	char			**here_doc;
	int				there_doc;
	char			**cmd;
	int				tcmd;
	int				use_heredoc;
	char			*path;
	char			**env;
	int				error;
	struct s_prompt	*next;
}					t_prompt;

typedef struct s_exec
{
	char			**env;
	int				fd_in;
	int				fd_out;
	int				**pipefd;
	int				here_docfd[2];
	int				exit;
	pid_t			*pid;
}					t_exec;

/* -----------------PARSING----------------- */
/* struct_utils.c */
void				ft_fileadd_back(t_file **lst, t_file *new);
void				ft_promptadd_back(t_prompt **lst, t_prompt *new);
t_file				*ft_filelast(t_file *lst);
t_prompt			*ft_promptlast(t_prompt *lst);
void				ft_get_here_doc(char *str, t_prompt *cmd);

/* struct_utils2.c */
t_prompt			*ft_create_prompt(t_prompt **cmds, char **env);
t_file				*ft_create_file(t_file **cmds);
int					ft_check_conditions2(char c, char b);
void				ft_pass_quotes_env_var(char *str, int *r);

/* parse_file.c */
int					ft_parse_file(char *str, t_prompt *cmd);
char				*ft_get_env(char *str, char **env);
int					ft_envlen(char *env);
int					ft_get_env_size(char *str, char **env);

/* parse_utils.c */
int					ft_count_new_str(char *str);
char				*ft_trim_prompt(char *str);
int					ft_isheredoc(char *str);

/* parse_utils2.c */
int					ft_nextchar(char *str, int j, char c);
int					ft_is_present(char *str, char c);
int					ft_pass_quotes(char const *s, int i);
void				ft_increment(int *i, int *j);
int					ft_get_the_path(t_prompt *cmd, char **env,
						char **parsed_pipe);

/* check_parse.c */
int					ft_check_parsed_pipes(char *str);
int					ft_check_pipes(char **pipes, char **old_pipes, int t);
int					ft_check_prompt(char *str);

/* parse_quotes */
int					ft_parse_quotes(char **pipes, int j, int last_return,
						char **env);

/* parsed_quotes_utils.c */
void				ft_cpy_parsed_quotes_help(char *str, char *src, int *f);

/* get_env_var.c */
int					ft_get_env_var(char **str, int j, int last_return,
						char **env);

/* get_env_var_utils.c*/
void				ft_get_last_return_length(int last_return, int *i, int *r);
void				ft_get_last_return_cpy(char *str, int last_return, int *r);
void				ft_cpy_env_var(char *str, int *r, int *i);
int					ft_get_temp_var(int *i, char *str, int *f, char **env);
int					ft_cpy_temp_var(char *str, char *pipe, int *f, char **env);

/* get_env_var_utils2.c */
void				ft_cpy_env_var_name(char *src, char *env_var, int *r);
int					ft_check_conditions(char c);
char				*ft_no_env(char *str);
int					ft_which_len(char *env, char *str);
int					ft_conditions(char c);

/* ft_split_minishell.c */
char				**ft_split_minishell(char const *s, char c);

/* ft_split_minishell_utils.c */
void				ft_fill_minishell_split(char const *s, char c, int *j,
						char *r);

/* cpy_env_var.c */
char				**ft_rep_env_var(char **env);
int					ft_tab_size(char **tab);

/* big_free.c */
void				ffa(t_prompt *prompt, char **pipes, char **pipes2);
void				ft_free_tab_n(char **tab, int n);
void				ft_free_exec(t_exec *exec);

/* parsing.c */
t_prompt			*ft_parse(char *str, int last_return, char **env);

/* -----------------EXEC----------------- */
/* exec_utils.c */
char				*get_path(char *cmd, char **env);
int					ft_get_signal(t_exec *exec, t_prompt *prompt, int *i);

/* int					open_file(t_file *s); */
void				open_in_out(t_prompt *prompt, t_exec *exec, int i);
int					ft_exec(t_prompt *prompt, t_exec *exec, int i);

/* exec.c */
void				ft_free_pipe(int **pipe, int size);
int					ft_size(t_prompt *prompt);
void				free_tab(char **tab);
void				kill_pid(t_exec *exec, int sigcode, int j);
int					exece(t_prompt *prompt, t_exec *exec);
int					signal_exit(t_exec *exec, int i[4]);

/* process.c */
int					ft_pipe(t_prompt *prompt, t_exec *exec, int i);
int					ft_process(t_prompt *prompt, t_exec *exec, int i);
void				ft_here_doc(t_prompt *prompt, t_exec *exec, int i);

int					ft_strstr_heredoc(char *s1, char *s2);
/* utils.c */
char				*ft_strstr(const char *s1, const char *s2);
int					ft_shlvl(t_exec *exec);
/* -----------------BULTINS----------------- */
/* ft_pwd.c */
int					ft_pwd(void);
int					ft_env(char **env);
int					ft_exit(t_prompt *prompt, int i);
/* ft_unset.c */
int					ft_unset(t_prompt *prompt, t_exec *exec, int k);
int					find_index(char **env, char *str);
char				**remove_index(t_exec *exec, int index);
/* ft_export.c */
int					ft_export(t_prompt *prompt, t_exec *exec, int j);

/* ft_echo.c */
int					ft_echo(t_prompt *prompt, t_exec *exec);

/* ft_cd.c */
int					ft_cd(t_prompt *prompt, t_exec *exec, int i);

void				sig_init(void);
void				ft_signal_value(int *last_return);
int					check_numeric(char *str);
int					ft_bultins(t_prompt *prompt, t_exec *exec, int i);
void				ft_sighandle_process(int sigcode);
void				ft_sighandle_heredoc(int sigcode);
char				*ft_strdup_x(char *s);
int					ft_is_present_x(char *str, char c);
void				ft_print_export_error(t_prompt *prompt, int *i);
void				ft_error_climber(t_prompt **prompt);
#endif
