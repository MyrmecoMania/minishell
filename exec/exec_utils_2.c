/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils_2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ticouvre <ticouvre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/20 11:22:51 by ticouvre          #+#    #+#             */
/*   Updated: 2024/03/22 18:21:13 by ticouvre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_free_pipe(int **pipe, int size)
{
	int	i;

	i = 0;
	while (i < size)
		free(pipe[i++]);
	free(pipe);
}

int	ft_size(t_prompt *prompt)
{
	t_prompt	*temp;
	int			t;

	t = 0;
	temp = prompt;
	while (temp)
	{
		t++;
		temp = temp->next;
	}
	return (t);
}

void	free_tab(char **tab)
{
	size_t	i;

	i = 0;
	while (tab[i])
	{
		free(tab[i]);
		i++;
	}
	free(tab);
}

void	kill_pid(t_exec *exec, int sigcode, int j)
{
	int	i;

	i = 0;
	while (i <= j)
	{
		kill(exec->pid[i], sigcode);
		i++;
	}
}
