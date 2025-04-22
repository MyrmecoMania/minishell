/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_file.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: enorie <enorie@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/08 22:12:17 by enorie            #+#    #+#             */
/*   Updated: 2024/03/23 12:52:54 by enorie           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_parse_infile(char *str, t_prompt *cmd)
{
	t_file	*file;

	if (str[1] == '<')
	{
		cmd->here_doc[cmd->there_doc] = ft_strdup(str + 2);
		if (!cmd->here_doc[cmd->there_doc])
			return (1);
		cmd->there_doc += 1;
	}
	else
	{
		file = ft_create_file(&(cmd->file));
		if (!file)
			return (1);
		file->file = ft_strdup(str + 1);
		if (!file->file)
			return (1);
		file->mode = 4;
	}
	ft_get_here_doc(str, cmd);
	return (0);
}

int	ft_parse_file(char *str, t_prompt *cmd)
{
	t_file	*file;

	if (str[0] == '>')
	{
		file = ft_create_file(&(cmd->file));
		if (!file)
			return (1);
		if (str[1] == '>')
			file->file = ft_strdup(str + 2);
		else
			file->file = ft_strdup(str + 1);
		if (!file->file)
			return (1);
		if (str[1] == '>')
			file->mode = APPEND;
		else
			file->mode = TRUNC;
	}
	else
		if (ft_parse_infile(str, cmd))
			return (1);
	return (0);
}

int	ft_get_env_size(char *str, char **env)
{
	char	*temp;
	int		r;

	temp = ft_get_env(str, env);
	if (temp)
	{
		r = ft_strlen(temp);
		free(temp);
	}
	else
		r = 0;
	return (r);
}

int	ft_envlen(char *env)
{
	int	i;

	i = 0;
	if (!env)
		return (0);
	while (env[i] != '=')
		i++;
	return (i);
}

char	*ft_get_env(char *str, char **env)
{
	char	*temp;
	int		i[5];

	i[3] = 0;
	i[4] = ft_strlen(str);
	i[0] = i[4];
	i[1] = 0;
	if (str[0] == '$' && !str[1])
		return (ft_no_env(str));
	i[2] = ft_which_len(env[i[3]], str);
	while (env[i[3]] && ft_strncmp(env[i[3]], str + 1, i[2]))
	{
		i[3]++;
		i[2] = ft_which_len(env[i[3]], str);
	}
	if (!env[i[3]])
		return (ft_no_env(str));
	temp = malloc(sizeof(char) * (ft_strlen(env[i[3]] + i[4]) + 1));
	if (!temp)
		return (NULL);
	while (env[i[3]][i[0]])
		temp[i[1]++] = env[i[3]][i[0]++];
	temp[i[1]] = '\0';
	return (temp);
}
