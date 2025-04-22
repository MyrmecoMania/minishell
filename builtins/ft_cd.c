/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ticouvre <ticouvre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/12 11:54:05 by ticouvre          #+#    #+#             */
/*   Updated: 2024/03/23 09:10:04 by ticouvre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <dirent.h>
#include <sys/types.h>

int	change_oldpwd(t_exec *exec)
{
	int		i;
	char	*tmp;

	i = 0;
	while (ft_strstr(exec->env[i], "OLDPWD=") == NULL && exec->env[i])
		i++;
	if (ft_strstr(exec->env[i], "OLDPWD=") == NULL)
		return (1);
	tmp = ft_strjoin("OLDPWD=", exec->env[find_index(exec->env, "PWD")] + 4);
	if (!tmp)
		return (-1);
	free(exec->env[i]);
	exec->env[i] = tmp;
	return (0);
}

int	change_pwd(t_exec *exec)
{
	int		i;
	char	str[4096];

	i = 0;
	if (!getcwd(str, 4096))
		return (0);
	while (ft_strstr(exec->env[i], "PWD") == NULL && exec->env[i])
		i++;
	if (ft_strstr(exec->env[i], "PWD") == NULL)
		return (1);
	free(exec->env[i]);
	exec->env[i] = ft_strjoin("PWD=", str);
	if (!exec->env[i])
		return (-1);
	return (0);
}

int	change_env(t_exec *exec)
{
	int	i;

	if (find_index(exec->env, "PWD") != -1)
	{
		if (change_oldpwd(exec) == -1)
			return (-1);
		if (change_pwd(exec) == -1)
			return (-1);
	}
	else
	{
		i = find_index(exec->env, "OLDPWD");
		if (i != -1)
			exec->env = remove_index(exec, i);
		if (!exec->env)
			return (-1);
	}
	return (0);
}

int	cd_line(t_prompt *prompt)
{
	DIR	*fd;

	fd = opendir(prompt->cmd[1]);
	if (!prompt->cmd[1] || fd == NULL)
	{
		printf("ok");
		ft_putstr_fd("cd: ", 2);
		ft_putstr_fd(prompt->cmd[1], 2);
		ft_putstr_fd(": No such file or directory\n", 2);
		return (1);
	}
	closedir(fd);
	return (0);
}

int	ft_cd(t_prompt *prompt, t_exec *exec, int i)
{
	if (i != 0 || ft_size(prompt) != 1)
		return (cd_line(prompt));
	if (!prompt->cmd[1])
	{
		ft_putstr_fd("cd: ", 2);
		ft_putstr_fd(prompt->cmd[1], 2);
		ft_putstr_fd(": No such file or directory\n", 2);
		return (1);
	}
	if (prompt->tcmd > 2)
	{
		ft_putstr_fd("cd: too many arguments\n", 2);
		return (1);
	}
	if (chdir(prompt->cmd[1]) == -1)
	{
		ft_putstr_fd("cd: ", 2);
		ft_putstr_fd(prompt->cmd[1], 2);
		ft_putstr_fd(": No such file or directory\n", 2);
		return (1);
	}
	if (change_env(exec) == -1)
		return (-1);
	return (0);
}
