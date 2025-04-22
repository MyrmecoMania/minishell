/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ticouvre <ticouvre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/20 10:38:25 by ticouvre          #+#    #+#             */
/*   Updated: 2024/03/22 11:51:40 by ticouvre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	count_outfile(t_prompt *prompt)
{
	int		i;
	t_file	*tmp;

	i = 0;
	tmp = prompt->file;
	while (tmp)
	{
		if (tmp->mode == 1 || tmp->mode == 2)
			i++;
		tmp = tmp->next;
	}
	return (i);
}

int	count_infile(t_prompt *prompt)
{
	int		i;
	t_file	*tmp;

	i = 0;
	tmp = prompt->file;
	while (tmp)
	{
		if (tmp->mode == 4)
			i++;
		tmp = tmp->next;
	}
	return (i);
}

int	open_file(t_file *s, t_exec *exec, int i)
{
	int	fd;

	fd = -5;
	if (s->mode == 4)
		fd = open(s->file, O_RDONLY);
	else if (s->mode == 1)
		fd = open(s->file, O_CREAT | O_WRONLY | O_APPEND, 0777);
	else if (s->mode == 2)
		fd = open(s->file, O_CREAT | O_TRUNC | O_WRONLY, 0777);
	if (fd == -1)
	{
		if (exec->fd_in > 0)
			close(exec->fd_in);
		if (exec->fd_out > 0)
			close(exec->fd_out);
		close(exec->pipefd[i][1]);
		close(exec->pipefd[i][0]);
		perror(s->file);
		exit(1);
	}
	return (fd);
}

void	open_line(t_prompt *prompt, t_file *temp, t_exec *exec, int j[5])
{
	(void)prompt;
	if (temp->mode == 1 || temp->mode == 2)
	{
		exec->fd_out = open_file(temp, exec, j[4]);
		j[1]++;
		if (j[1] == j[3])
		{
			if ((!ft_strncmp(temp->file, "/dev/stdout", 12) && prompt->next))
			{
				close(exec->fd_out);
				exec->fd_out = open("/dev/null",
						O_CREAT | O_WRONLY | O_APPEND, 0777);
				dup2(exec->fd_out, 1);
				close(exec->fd_out);
			}
			else
				dup2(exec->fd_out, 1);
		}
		else
			close(exec->fd_out);
	}
}

void	open_in_out(t_prompt *prompt, t_exec *exec, int i)
{
	t_file	*temp;
	int		j[5];

	temp = prompt->file;
	exec->fd_in = -5;
	exec->fd_out = -5;
	j[0] = 0;
	j[1] = 0;
	j[2] = count_infile(prompt);
	j[3] = count_outfile(prompt);
	j[4] = i;
	while (temp)
	{
		if (temp->mode == 4)
		{
			exec->fd_in = open_file(temp, exec, i);
			j[0]++;
			if (prompt->use_heredoc == 4 && j[0] == j[2])
				dup2(exec->fd_in, 0);
			else
				close(exec->fd_in);
		}
		open_line(prompt, temp, exec, j);
		temp = temp->next;
	}
}
