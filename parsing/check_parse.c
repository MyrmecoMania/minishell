/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_parse.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: enorie <enorie@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/02 11:56:33 by enorie            #+#    #+#             */
/*   Updated: 2024/03/23 12:53:47 by enorie           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_pass_quotes_check(char *str, int *c)
{
	if (str[c[2]] && str[c[2]] == '\'')
	{
		ft_increment(&c[2], &c[0]);
		while (str[c[2]] && str[c[2]] != '\'')
			c[2]++;
		if (str[c[2]])
			ft_increment(&c[2], &c[0]);
	}
	if (str[c[2]] && str[c[2]] == '\"')
	{
		ft_increment(&c[2], &c[1]);
		while (str[c[2]] && str[c[2]] != '\"')
			c[2]++;
		if (str[c[2]])
			ft_increment(&c[2], &c[1]);
	}
}

int	ft_check_parsed_pipes(char *str)
{
	int	c[3];

	c[2] = 0;
	c[0] = 0;
	c[1] = 0;
	while (str[c[2]])
	{
		ft_pass_quotes_check(str, c);
		if (str[c[2]] && str[c[2]] != '\"' && str[c[2]] != '\'')
			c[2]++;
	}
	if ((c[0] && c[0] % 2 != 0) || (c[1] && c[1] % 2 != 0))
		return (ft_putstr_fd("parse error: \' or \" not closed\n", 2), 1);
	return (0);
}

int	ft_choose_error(char **pipes, int *i, char **old_pipes, int t)
{
	if ((!pipes[i[0] + 1] && !old_pipes[t + 1]))
		return (2);
	else if ((!pipes[i[0] + 1] && old_pipes[t + 1]))
		return (1);
	else if ((pipes[i[0]][i[1] - 1] == '<' && (ft_strlen(pipes[i[0]]) >= 2)
		&& pipes[i[0]][i[1] - 2] == '<') || ((pipes[i[0]][i[1] - 1] == '<'
			&& (ft_strlen(pipes[i[0]])) >= 3) && pipes[i[0]][i[1] - 2] == '<'
			&& pipes[i[0]][i[1] - 3] == '<'))
		return (3);
	else if (pipes[i[0]][i[1] - 1] == '<' && !((ft_strlen(pipes[i[0]])
		>= 2) && pipes[i[0]][i[1] - 2] == '<'))
		return (4);
	else if (pipes[i[0]][i[1] - 1] == '>' && (ft_strlen(pipes[i[0]])
		>= 2) && pipes[i[0]][i[1] - 2] == '>')
		return (5);
	else if (pipes[i[0]][i[1] - 1] == '>' && !((ft_strlen(pipes[i[0]])
		>= 2) && pipes[i[0]][i[1] - 2] == '>'))
		return (6);
	return (0);
}

int	ft_check_pipes(char **pipes, char **old_pipes, int t)
{
	int	i[3];

	i[0] = -1;
	while (pipes[++i[0]])
	{
		i[1] = 0;
		while (pipes[i[0]][i[1]] && pipes[i[0]][i[1]] == '>')
			i[1]++;
		if (i[1] > 2 || (i[1] > 0 && pipes[i[0]][i[1]] == '<'))
			return (5);
		while (pipes[i[0]][i[1]] && pipes[i[0]][i[1]] == '<')
			i[1]++;
		if (i[1] > 2 || (i[1] > 0 && pipes[i[0]][i[1]] == '>'))
			return (3);
		while (pipes[i[0]][i[1]])
			i[1]++;
		if (i[1] > 0 && (pipes[i[0]][i[1] - 1] == '<'
			|| pipes[i[0]][i[1] - 1] == '>' || pipes[i[0]][i[1] - 1] == '|'))
		{
			i[2] = ft_choose_error(pipes, i, old_pipes, t);
			if (i[2])
				return (i[2]);
		}
	}
	return (0);
}

int	ft_check_prompt(char *str)
{
	int	i;

	i = 0;
	while (str[i] && (str[i] == ' ' || (str[i] >= 9 && str[i] <= 13)))
		i++;
	if (!str[i])
		return (1);
	if (str[i] == '|')
		return (ft_putstr_fd(ERROR_MSG1, 2), 1);
	return (0);
}
