/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: enorie <enorie@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/16 14:21:29 by ticouvre          #+#    #+#             */
/*   Updated: 2024/03/23 11:11:21 by enorie           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_pipe_line(t_exec *exec, int i)
{
	close(exec->pipefd[i][1]);
	if (i > 0)
		close(exec->pipefd[i - 1][0]);
}

int	ft_check_builtins(int i, char *cmd)
{
	if (i != 0 || !cmd || !(!ft_strncmp(cmd, "unset", 6)
			|| !ft_strncmp(cmd, "cd", 3)
			|| !ft_strncmp(cmd, "export", 7)))
		return (1);
	return (0);
}

int	ft_pipe(t_prompt *prompt, t_exec *exec, int i)
{
	signal(SIGINT, ft_sighandle_process);
	if (!prompt->there_doc)
		signal(SIGQUIT, ft_sighandle_process);
	if (pipe(exec->pipefd[i]) == -1)
		exit(EXIT_FAILURE);
	if (ft_check_builtins(i, prompt->cmd[0]))
		exec->pid[i] = fork();
	else
	{
		exec->pid[i] = 0;
		close(exec->pipefd[i][1]);
		return (close(exec->pipefd[i][0]), ft_bultins(prompt, exec, i));
	}
	if (exec->pid[i] == -1)
		exit(EXIT_FAILURE);
	else if (exec->pid[i] == 0)
		return (ft_process(prompt, exec, i));
	else
		ft_pipe_line(exec, i);
	return (0);
}

int	ft_process(t_prompt *prompt, t_exec *exec, int i)
{
	signal(SIGINT, SIG_DFL);
	if (prompt->there_doc != 0)
		ft_here_doc(prompt, exec, i);
	signal(SIGQUIT, SIG_DFL);
	open_in_out(prompt, exec, i);
	if (i != 0 && exec->fd_in == -5 && !prompt->there_doc)
		dup2(exec->pipefd[i - 1][0], 0);
	if (prompt->next && exec->fd_out == -5)
		dup2(exec->pipefd[i][1], 1);
	if (i > 0)
		close(exec->pipefd[i - 1][0]);
	close(exec->pipefd[i][1]);
	close(exec->pipefd[i][0]);
	if (exec->fd_out > 0)
		close(exec->fd_out);
	if (exec->fd_in > 0)
		close(exec->fd_in);
	if (prompt->cmd[0])
		return (ft_exec(prompt, exec, i));
	else
		exit(EXIT_SUCCESS);
}

int	ft_strstr_heredoc(char *s1, char *s2)
{
	size_t	i;

	i = 0;
	while (s1[i] && s1[i] == s2[i] && s2[i])
		i++;
	return (s1[i] - s2[i]);
}
