/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_quotes.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: enorie <enorie@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/08 22:14:30 by enorie            #+#    #+#             */
/*   Updated: 2024/03/23 12:52:36 by enorie           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_parse_double_quotes(char *str, int *i, int *f, char **env)
{
	while (str[*i] != '\"')
	{
		if (str[*i] == '$' && str[*i + 1] && str[*i + 1] == '?')
			ft_get_last_return_length(f[1], i, &f[0]);
		else if (str[*i] == '$')
		{
			if (ft_get_temp_var(i, str, f, env))
				return (1);
		}
		else
			ft_increment(i, f);
	}
	return (0);
}

int	ft_cpy_double_quotes(char *str, char *pipe, int *f, char **env)
{
	if (str[f[2]] == '$' && str[f[2] + 1] && str[f[2] + 1] == '?')
		ft_cpy_env_var(pipe, f, &f[2]);
	else if (str[f[2]] == '$')
	{
		if (ft_cpy_temp_var(str, pipe, f, env))
			return (1);
	}
	else
		pipe[f[0]++] = str[(f[2])++];
	return (0);
}

int	ft_count_parsed_quotes(char *str, int *f, char **env)
{
	int	i;

	i = 0;
	while (str[i])
	{
		while (str[i] && str[i] != '\'' && str[i] != '\"')
			ft_increment(&i, f);
		if (str[i] && str[i] == '\'')
		{
			i++;
			while (str[i] != '\'')
				ft_increment(&i, f);
			i++;
		}
		if (str[i] && str[i] == '\"')
		{
			i++;
			if (ft_parse_double_quotes(str, &i, f, env))
				return (1);
			i++;
		}
	}
	return (0);
}

int	ft_cpy_parsed_quotes(char *str, char *src, int *f, char **env)
{
	ft_cpy_parsed_quotes_help(str, src, f);
	if (src[f[2]] && src[f[2]] == '\"')
	{
		(f[2])++;
		while (src[f[2]] && src[f[2]] != '\"')
		{
			if (src[f[2]] == 0 || (src[f[2]] <= 15 && src[f[2]] >= 7))
			{
				str[f[0]++] = '\\';
				str[f[0]++] = src[(f[2])++];
			}
			if (ft_cpy_double_quotes(src, str, f, env))
				return (1);
		}
		(f[2])++;
	}
	return (0);
}

int	ft_parse_quotes(char **pipes, int j, int last_return, char **env)
{
	int		f[3];
	char	*temp2;

	f[0] = 0;
	f[1] = last_return;
	if (ft_count_parsed_quotes(pipes[j], f, env))
		return (1);
	temp2 = ft_strdup(pipes[j]);
	if (!temp2)
		return (1);
	free(pipes[j]);
	pipes[j] = malloc(sizeof(char) * (f[0] + 1));
	if (!pipes[j])
		return (free(temp2), 1);
	f[2] = 0;
	f[0] = 0;
	while (temp2[f[2]])
	{
		if (ft_cpy_parsed_quotes(pipes[j], temp2, f, env))
			return (free(temp2), 1);
	}
	pipes[j][f[0]] = '\0';
	return (free(temp2), 0);
}
