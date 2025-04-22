/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: enorie <enorie@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/29 17:20:43 by ticouvre          #+#    #+#             */
/*   Updated: 2024/03/23 10:49:05 by enorie           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_exec_error(t_prompt *prompt, t_exec *exec)
{
	if (prompt->path && execve(prompt->path, prompt->cmd, exec->env) == -1)
	{
		if (ft_strchr(prompt->cmd[0], '/'))
		{
			if (access(prompt->cmd[0], F_OK) == 0)
			{
				ft_putstr_fd(prompt->cmd[0], 2);
				ft_putstr_fd(": Is a directory\n", 2);
				exit(126);
			}
			else
			{
				ft_putstr_fd(prompt->cmd[0], 2);
				ft_putstr_fd(": No such file or directory\n", 2);
				exit(127);
			}
		}
		ft_putstr_fd(prompt->cmd[0], 2);
		ft_putstr_fd(": command not found\n", 2);
		free(exec->pid);
		exit(127);
	}
}

int	ft_exec(t_prompt *prompt, t_exec *exec, int i)
{
	int	res;

	if (exec->env[0] == NULL)
		exit(EXIT_FAILURE);
	if (prompt->path == NULL && access(prompt->cmd[0], F_OK) == 0)
		prompt->path = prompt->cmd[0];
	res = ft_bultins(prompt, exec, i);
	if (res == ERROR_MALLOC)
		exit(ERROR_MALLOC);
	if (res != -5)
		exit(res);
	ft_exec_error(prompt, exec);
	if (prompt->path == NULL)
	{
		ft_putstr_fd(prompt->cmd[0], 2);
		ft_putstr_fd(": command not found\n", 2);
		free(exec->pid);
		exit(127);
	}
	return (0);
}

int	ft_get_signal(t_exec *exec, t_prompt *prompt, int *i)
{
	i[4] = signal_exit(exec, i);
	if (i[4] != -1)
		return (i[4]);
	if (prompt->cmd[0] && i[0] == 0 && ft_size(prompt) == 1
		&& (!ft_strncmp(prompt->cmd[0], "cd", 3)))
		i[5]++;
	return (0);
}
