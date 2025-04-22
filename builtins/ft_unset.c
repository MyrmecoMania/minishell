/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: enorie <enorie@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/28 14:43:52 by ticouvre          #+#    #+#             */
/*   Updated: 2024/03/20 11:32:17 by enorie           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	find_index(char **env, char *str)
{
	char	*tmp;
	int		i;

	i = 0;
	tmp = ft_strjoin(str, "=");
	if (!tmp)
		return (0);
	while (ft_strstr(env[i], tmp) == NULL && env[i])
		i++;
	if (ft_strstr(env[i], tmp) != NULL)
	{
		free(tmp);
		return (i);
	}
	free(tmp);
	return (-1);
}

char	**remove_index(t_exec *exec, int index)
{
	int		i[2];
	char	**tab;

	i[0] = 0;
	while (exec->env[i[0]])
		i[0]++;
	tab = malloc(sizeof(char *) * i[0]);
	if (!tab)
		return (NULL);
	i[0] = 0;
	i[1] = 0;
	while (exec->env[i[0]])
	{
		if (i[0] == index)
			i[0]++;
		else
		{
			tab[i[1]] = ft_strdup(exec->env[i[0]++]);
			if (!tab[i[1]])
				return (ft_free_tab_n(tab, i[1]), NULL);
			i[1]++;
		}
	}
	tab[i[1]] = NULL;
	return (tab);
}

int	ft_unset(t_prompt *prompt, t_exec *exec, int k)
{
	int		i;
	int		j;
	char	**env;

	i = 1;
	j = 0;
	if (prompt->next || k != 0)
		return (0);
	while (prompt->cmd[i])
	{
		j = find_index(exec->env, prompt->cmd[i]);
		if (!j)
			return (-1);
		if (j != -1)
		{
			env = remove_index(exec, j);
			if (!env)
				return (-1);
			free_tab(exec->env);
			exec->env = env;
		}
		i++;
	}
	return (0);
}
