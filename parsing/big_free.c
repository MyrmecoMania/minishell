/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   big_free.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: enorie <enorie@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/12 16:03:54 by enorie            #+#    #+#             */
/*   Updated: 2024/03/22 14:38:56 by enorie           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_free_files(t_prompt *prompt)
{
	t_file		*temp;

	while (prompt->file)
	{
		free(prompt->file->file);
		temp = prompt->file->next;
		free(prompt->file);
		prompt->file = temp;
	}
}

void	ft_free_tabss(t_prompt *prompt)
{
	if (prompt->path)
		free(prompt->path);
	if (prompt->tcmd)
	{
		while (prompt->tcmd)
		{
			free(prompt->cmd[prompt->tcmd - 1]);
			prompt->tcmd--;
		}
	}
	free(prompt->cmd);
	if (prompt->there_doc)
	{
		while (prompt->there_doc)
		{
			free(prompt->here_doc[prompt->there_doc - 1]);
			prompt->there_doc--;
		}
	}
	free(prompt->here_doc);
}

void	ffa(t_prompt *prompt, char **pipes, char **pipes2)
{
	t_prompt	*temp2;
	int			i;

	while (prompt)
	{
		ft_free_tabss(prompt);
		ft_free_files(prompt);
		temp2 = prompt->next;
		free(prompt);
		prompt = temp2;
	}
	i = 0;
	if (pipes)
	{
		while (pipes[i])
			free(pipes[i++]);
		free(pipes);
	}
	i = 0;
	if (pipes2)
	{
		while (pipes2[i])
			free(pipes2[i++]);
		free(pipes2);
	}
}

void	ft_free_tab_n(char **tab, int n)
{
	int	i;

	i = 0;
	while (i < n)
	{
		free(tab[i]);
	}
	free(tab);
}

void	ft_free_exec(t_exec *exec)
{
	int	i;

	i = 0;
	if (exec)
	{
		if (exec->env)
		{
			while (exec->env[i])
				free(exec->env[i++]);
			free(exec->env);
		}
		free(exec);
	}
}
