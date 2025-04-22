/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: enorie <enorie@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/20 13:15:07 by ticouvre          #+#    #+#             */
/*   Updated: 2024/03/23 11:45:53 by enorie           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	signal_here_doc(t_prompt *prompt, t_exec *exec, int i, char *res)
{
	if (g_signal != 0)
	{
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
		free(res);
		if (prompt->use_heredoc == 3)
			dup2(exec->here_docfd[0], 0);
		exit(130);
	}
}

int	here_doc_line(t_prompt *prompt, t_exec *exec, int i, char *res)
{
	signal_here_doc(prompt, exec, i, res);
	if (!res)
	{
		free(res);
		if (prompt->use_heredoc == 3)
			dup2(exec->here_docfd[0], 0);
		close(exec->here_docfd[0]);
		close(exec->here_docfd[1]);
		return (1);
	}
	return (0);
}

void	line_here(t_prompt *prompt, t_exec *exec, char *res)
{
	free(res);
	if (prompt->use_heredoc == 3)
		dup2(exec->here_docfd[0], 0);
	close(exec->here_docfd[0]);
	close(exec->here_docfd[1]);
}

void	ft_here_doc(t_prompt *prompt, t_exec *exec, int i)
{
	char	*res;
	int		j;

	j = 0;
	pipe(exec->here_docfd);
	while (1)
	{
		res = readline("> ");
		if (here_doc_line(prompt, exec, i, res) == 1)
			return ;
		if (!ft_strncmp(prompt->here_doc[j], res, ft_strlen(res) - 1))
		{
			if (!prompt->here_doc[j + 1])
				return (line_here(prompt, exec, res));
			else
				j++;
		}
		else if (!prompt->here_doc[j + 1])
		{
			ft_putstr_fd(res, exec->here_docfd[1]);
			ft_putstr_fd("\n", exec->here_docfd[1]);
		}
		free(res);
	}
}
