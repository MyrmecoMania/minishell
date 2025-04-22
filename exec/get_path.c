/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_path.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ticouvre <ticouvre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/19 17:21:29 by ticouvre          #+#    #+#             */
/*   Updated: 2024/03/19 17:32:49 by ticouvre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_path_line(char *cmd, char **path, int i)
{
	char	*path_slash;
	char	*pathname;

	i = 0;
	while (path[i])
	{
		path_slash = ft_strjoin(path[i], "/");
		if (!path_slash)
			return ("malloc");
		pathname = ft_strjoin(path_slash, cmd);
		if (!pathname)
			return ("malloc");
		if (access(pathname, F_OK) == 0)
		{
			free_tab(path);
			free(path_slash);
			return (pathname);
		}
		free(path_slash);
		free(pathname);
		i++;
	}
	free_tab(path);
	return (NULL);
}

char	*get_path(char *cmd, char **env)
{
	char	**path;
	int		i;

	i = 0;
	while (ft_strstr(env[i], "PATH=") == NULL && env[i])
		i++;
	if (ft_strstr(env[i], "PATH=") != NULL && env[i])
	{
		path = ft_split(env[i] + 5, ':');
		if (!path)
			return ("malloc");
	}
	else
		return (NULL);
	return (get_path_line(cmd, path, i));
}
