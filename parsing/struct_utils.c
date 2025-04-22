/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ticouvre <ticouvre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/01 13:03:28 by enorie            #+#    #+#             */
/*   Updated: 2024/02/16 13:47:51 by ticouvre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_prompt	*ft_promptlast(t_prompt *lst)
{
	t_prompt	*t;

	if (!lst)
		return (NULL);
	t = lst;
	while (t->next != NULL)
		t = t->next;
	return (t);
}

t_file	*ft_filelast(t_file *lst)
{
	t_file	*t;

	if (!lst)
		return (NULL);
	t = lst;
	while (t->next != NULL)
		t = t->next;
	return (t);
}

void	ft_promptadd_back(t_prompt **lst, t_prompt *new)
{
	t_prompt	*t;

	if (lst)
	{
		if (*lst)
		{
			t = ft_promptlast((*lst));
			t->next = new;
		}
		else
			(*lst) = new;
	}
}

void	ft_fileadd_back(t_file **lst, t_file *new)
{
	t_file	*t;

	if (lst)
	{
		if (*lst)
		{
			t = ft_filelast((*lst));
			t->next = new;
		}
		else
			(*lst) = new;
	}
}

void	ft_get_here_doc(char *str, t_prompt *cmd)
{
	int	i;

	cmd->use_heredoc = USE_INFILE;
	if (!cmd->there_doc)
		return ;
	i = ft_strlen(str) - 1;
	while (i > 0 && str[i] != '<')
		i--;
	if (i > 0 && str[i - 1] == '<')
		cmd->use_heredoc = USE_HEREDOC;
}
