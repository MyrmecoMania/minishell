/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct_utils2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: enorie <enorie@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/02 19:16:20 by enorie            #+#    #+#             */
/*   Updated: 2024/03/23 12:52:08 by enorie           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_prompt	*ft_create_prompt(t_prompt **cmds, char **env)
{
	t_prompt	*prompt;

	prompt = malloc(sizeof(t_prompt));
	if (!prompt)
		return (NULL);
	prompt->file = NULL;
	prompt->next = NULL;
	prompt->cmd = NULL;
	prompt->here_doc = NULL;
	prompt->path = NULL;
	prompt->tcmd = 0;
	prompt->there_doc = 0;
	prompt->env = env;
	prompt->error = 0;
	ft_promptadd_back(cmds, prompt);
	return (prompt);
}

t_file	*ft_create_file(t_file **cmds)
{
	t_file		*file;

	file = malloc(sizeof(t_file));
	if (!file)
		return (NULL);
	file->next = NULL;
	ft_fileadd_back(cmds, file);
	return (file);
}

int	ft_check_conditions2(char c, char b)
{
	if (c && c == '$' && b && b == '?')
		return (0);
	if (c && !ft_isalnum(c) && c != '\"' && c != '\''
		&& (c != '$' || (c == '$' && !ft_isalnum(b))))
		return (1);
	return (0);
}

void	ft_pass_quotes_env_var(char *str, int *r)
{
	if (str[r[2]] == '\'')
	{
		ft_increment(&r[2], &r[0]);
		while (str[r[2]] != '\'')
			ft_increment(&r[2], &r[0]);
		ft_increment(&r[2], &r[0]);
	}
	if (str[r[2]] == '\"')
	{
		ft_increment(&r[2], &r[0]);
		while (str[r[2]] != '\"')
			ft_increment(&r[2], &r[0]);
		ft_increment(&r[2], &r[0]);
	}
}

void	ft_error_climber(t_prompt **prompt)
{
	t_prompt	*p;

	p = *prompt;
	while (p)
	{
		if (p->error != 0)
		{
			(*prompt)->error = p->error;
			return ;
		}
		p = p->next;
	}		
}
