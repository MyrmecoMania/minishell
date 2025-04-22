/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: enorie <enorie@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/06 13:29:30 by enorie            #+#    #+#             */
/*   Updated: 2024/03/23 12:52:23 by enorie           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_is_present(char *str, char c)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == c)
			return (0);
		i++;
	}
	return (1);
}

int	ft_pass_quotes(char const *s, int i)
{
	if (s[i] == '\'')
	{
		i++;
		while (s[i] != '\'')
			i++;
		i++;
	}
	if (s[i] == '\"')
	{
		i++;
		while (s[i] != '\"')
			i++;
		i++;
	}
	return (i);
}

int	ft_nextchar(char *str, int j, char c)
{
	int	i;

	i = j;
	while (str[i] && (str[i] == ' ' || (str[i] >= 9 && str[i] <= 13)))
		i++;
	if (!str[i] || ((c == '<' || c == '>') && (str[i] != '<' && str[i] != '>')))
		return (0);
	return (1);
}

void	ft_increment(int *i, int *j)
{
	(*i)++;
	(*j)++;
}

int	ft_get_the_path(t_prompt *cmd, char **env, char **parsed_pipe)
{
	cmd->path = get_path(cmd->cmd[0], env);
	if (cmd->path && !ft_strncmp(cmd->path, "malloc", 7))
		return (ffa(cmd, parsed_pipe, NULL), 1);
	return (0);
}
