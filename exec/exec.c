/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: enorie <enorie@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/29 17:20:40 by ticouvre          #+#    #+#             */
/*   Updated: 2024/03/23 11:30:04 by enorie           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	g_signal;

int	init_pipefd(t_exec *exec, t_prompt *prompt, int i[4])
{
	i[0] = 0;
	i[1] = 0;
	i[2] = ft_size(prompt);
	exec->pipefd = malloc(sizeof(int *) * i[2]);
	if (!exec->pipefd)
		return (ERROR_MALLOC);
	while (i[1] < i[2])
	{
		exec->pipefd[i[1]] = malloc(sizeof(int) * 2);
		if (!exec->pipefd[i[1]])
			return (ERROR_MALLOC);
		i[1]++;
	}
	return (0);
}

int	signal_exit(t_exec *exec, int i[4])
{
	if (g_signal != 0)
	{
		kill_pid(exec, g_signal, i[0]);
		if (g_signal == SIGINT)
		{
			g_signal = 0;
			return (130);
		}
		else if (g_signal == SIGQUIT)
		{
			g_signal = 0;
			return (131);
		}
		else
		{
			g_signal = 0;
			return (0);
		}
	}
	return (-1);
}

int	wait_pid_free(t_exec *exec, int i[6])
{
	if (i[5] == 1)
	{
		ft_free_pipe(exec->pipefd, i[2]);
		return (i[3]);
	}
	i[1] = 0;
	while (i[1] < i[0])
		waitpid(exec->pid[i[1]++], &i[3], 0);
	close(exec->pipefd[i[0] - 1][0]);
	ft_free_pipe(exec->pipefd, i[2]);
	return (WEXITSTATUS(i[3]));
}

void	ft_isexit(t_exec *exec, t_prompt *prompt, int *i)
{
	exec->exit--;
	i[3] = ft_exit(prompt, i[0]);
	i[5] = 1;
}

int	exece(t_prompt *prompt, t_exec *exec)
{
	int	i[6];

	i[0] = 0;
	i[5] = 0;
	if (init_pipefd(exec, prompt, i) == ERROR_MALLOC)
		return (ERROR_MALLOC);
	while (prompt)
	{
		if (prompt->cmd[0] && i[0] == 0 && ft_size(prompt) == 1
			&& (!ft_strncmp(prompt->cmd[0], "exit", 5)))
			ft_isexit(exec, prompt, i);
		else
		{
			i[3] = ft_pipe(prompt, exec, i[0]);
			if (i[3] == ERROR_MALLOC)
				return (ERROR_MALLOC);
		}
		if (ft_get_signal(exec, prompt, i))
			return (i[4]);
		prompt = prompt->next;
		i[0]++;
	}
	return (wait_pid_free(exec, i));
}
