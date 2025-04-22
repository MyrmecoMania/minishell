/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: enorie <enorie@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/12 09:32:52 by enorie            #+#    #+#             */
/*   Updated: 2024/03/23 12:29:50 by enorie           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_cpy_new_nev_var(char *temp, char *dest, char *src, char mode)
{
	int	i[3];

	i[0] = 0;
	i[1] = 0;
	i[2] = 0;
	if (mode == 'r')
	{
		while (dest[i[1]] != '=')
			temp[i[2]++] = dest[i[1]++];
	}
	else
	{
		while (dest[i[1]])
			temp[i[2]++] = dest[i[1]++];
	}
	while (src[i[0]] != '=')
		i[0]++;
	if (mode == 'c')
		i[0]++;
	while (src[i[0]])
		temp[i[2]++] = src[i[0]++];
	temp[i[2]] = '\0';
}

int	ft_replace_and_concat(char **dest, char *src, int p, char mode)
{
	int		i;
	int		j;
	int		t;
	char	*temp;

	i = 0;
	j = 0;
	t = 0;
	if (mode == 'c')
	{
		while (src[i] != '=')
			i++;
		i++;
		while (dest[p][j])
			ft_increment(&j, &t);
	}
	while (src[i])
		ft_increment(&i, &t);
	temp = malloc(sizeof(char) * (t + 1));
	if (!temp)
		return (1);
	ft_cpy_new_nev_var(temp, dest[p], src, mode);
	free(dest[p]);
	dest[p] = temp;
	return (0);
}

int	ft_replace(char **tab, char *value, int *t)
{
	int	i;
	int	j;

	j = 0;
	while (j < t[3])
	{
		i = 0;
		while (value[i] && value[i] != '+' && value[i] != '=')
			i++;
		if (value[i] && value[i] == '+' && value[i + 1] && value[i + 1] != '=')
			return (ft_putstr_fd("export: `", 2), ft_putstr_fd(value, 2),
				ft_putstr_fd("': not a valid identifier\n", 2), 1);
		else if (value[i] && !ft_strncmp(tab[j], value, ft_envlen(tab[j]))
			&& value[i] == '+' && value[i + 1] && value[i + 1] == '=')
			return (ft_replace_and_concat(tab, value, j, 'c'), 1);
		else if (value[i] && !ft_strncmp(tab[j], value, ft_envlen(tab[j])))
			return (ft_replace_and_concat(tab, value, j, 'r'), 1);
		j++;
	}
	return (0);
}

int	ft_cpy_modified_env(char **temp, t_prompt *prompt, int *i)
{
	while (i[2] < prompt->tcmd)
	{
		if (!ft_replace(temp, prompt->cmd[i[2]], i)
			&& !(ft_isalpha(prompt->cmd[i[2]][0])
			&& ft_is_present(prompt->cmd[i[2]], '=')))
		{
			if (ft_isalpha(prompt->cmd[i[2]][0])
				&& !ft_is_present(prompt->cmd[i[2]], '='))
			{
				if (!ft_is_present_x(prompt->cmd[i[2]], '+'))
					temp[i[1]] = ft_strdup_x(prompt->cmd[i[2]]);
				else
					temp[i[1]] = ft_strdup(prompt->cmd[i[2]]);
				i[2]++;
				if (!temp[i[1]])
					return (ft_free_tab_n(temp, i[1]), 1);
				ft_increment(&i[1], &i[3]);
			}
			else
				ft_print_export_error(prompt, i);
		}
		else
			i[2]++;
	}
	return (0);
}

int	ft_export(t_prompt *prompt, t_exec *exec, int j)
{
	int		i[4];
	char	**temp;

	i[0] = 0;
	i[1] = -1;
	i[2] = 1;
	if (prompt->next || j != 0)
		return (0);
	i[0] = ft_tab_size(exec->env);
	temp = malloc(sizeof(char *) * (i[0] + prompt->tcmd));
	if (!temp)
		return (-1);
	while (++i[1] < i[0])
	{
		temp[i[1]] = ft_strdup(exec->env[i[1]]);
		if (!temp[i[1]])
			return (ffa(NULL, temp, NULL), -1);
	}
	i[3] = i[0];
	if (ft_cpy_modified_env(temp, prompt, i))
		return (-1);
	temp[i[1]] = NULL;
	ffa(NULL, exec->env, NULL);
	exec->env = temp;
	return (0);
}
