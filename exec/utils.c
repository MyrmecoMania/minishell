/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: enorie <enorie@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/26 12:27:41 by ticouvre          #+#    #+#             */
/*   Updated: 2024/03/21 13:41:19 by enorie           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_strstr(const char *s1, const char *s2)
{
	size_t	i;

	i = 0;
	if (!s1 || !s2)
		return (NULL);
	while (s1[i] && s1[i] == s2[i])
		i++;
	if (s2[i] == '\0')
		return ((char *)s1 + i);
	return (0);
}

int	ft_bultins(t_prompt *prompt, t_exec *exec, int i)
{
	if (!ft_strncmp(prompt->cmd[0], "echo", 5))
		return (ft_echo(prompt, exec));
	if (!ft_strncmp(prompt->cmd[0], "cd", 3))
		return (ft_cd(prompt, exec, i));
	if (!ft_strncmp(prompt->cmd[0], "export", 5))
		return (ft_export(prompt, exec, i));
	if (!ft_strncmp(prompt->cmd[0], "pwd", 4))
		return (ft_pwd());
	if (!ft_strncmp(prompt->cmd[0], "unset", 6))
		return (ft_unset(prompt, exec, i));
	if (!ft_strncmp(prompt->cmd[0], "env", 4))
		return (ft_env(exec->env));
	if (!ft_strncmp(prompt->cmd[0], "exit", 5))
		return (ft_exit(prompt, i));
	return (-5);
}

int	ft_shlvl(t_exec *exec)
{
	int		i;
	int		j;
	char	*str;
	char	*tmp;

	i = 0;
	if (!exec->env)
		return (1);
	while (exec->env[i] && ft_strstr(exec->env[i], "SHLVL=") == NULL)
		i++;
	if (ft_strstr(exec->env[i], "SHLVL=") == NULL)
		return (1);
	str = exec->env[i] + 6;
	j = ft_atoi(str) + 1;
	free(exec->env[i]);
	tmp = ft_itoa(j);
	exec->env[i] = ft_strjoin("SHLVL=", tmp);
	if (!exec->env[i])
		return (ERROR_MALLOC);
	free(tmp);
	return (0);
}
