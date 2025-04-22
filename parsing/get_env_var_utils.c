/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_env_var_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: enorie <enorie@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/12 19:16:31 by enorie            #+#    #+#             */
/*   Updated: 2024/03/23 12:53:16 by enorie           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_get_last_return_length(int last_return, int *i, int *r)
{
	if (last_return < 0)
	{
		(*r)++;
		last_return *= -1;
	}
	else if (last_return == 0)
		(*r)++;
	while (last_return > 0)
	{
		(*r)++;
		last_return /= 10;
	}
	(*i) += 2;
}

void	ft_get_last_return_cpy(char *str, int last_return, int *r)
{
	if (last_return < 0)
	{
		str[(*r)++] = '-';
		last_return *= -1;
	}
	else if (last_return < 10)
		str[(*r)++] = last_return + '0';
	else
	{
		ft_get_last_return_cpy(str, last_return / 10, r);
		ft_get_last_return_cpy(str, last_return % 10, r);
	}
}

void	ft_cpy_env_var(char *str, int *r, int *i)
{
	ft_get_last_return_cpy(str, r[1], &r[0]);
	*i += 2;
}

int	ft_get_temp_var(int *i, char *str, int *f, char **env)
{
	int		r[2];
	char	*temp;

	r[1] = *i + 1;
	while (ft_check_conditions(str[r[1]]))
		r[1]++;
	temp = malloc(sizeof(char) * (r[1] - *i + 1));
	if (!temp)
		return (1);
	r[0] = 0;
	temp[r[0]++] = str[(*i)++];
	while (ft_check_conditions(str[*i]))
		temp[r[0]++] = str[(*i)++];
	temp[r[0]] = '\0';
	f[0] += ft_get_env_size(temp, env);
	free(temp);
	return (0);
}

int	ft_cpy_temp_var(char *str, char *pipe, int *f, char **env)
{
	int		t[2];
	char	*temp;
	char	*env_var;

	t[0] = f[2] + 1;
	while (ft_check_conditions(str[t[0]]))
		t[0]++;
	temp = malloc(sizeof(char) * (t[0] - f[2] + 1));
	if (!temp)
		return (1);
	t[1] = 0;
	temp[t[1]++] = str[(f[2])++];
	while (ft_check_conditions(str[f[2]]))
		temp[t[1]++] = str[(f[2])++];
	temp[t[1]] = '\0';
	env_var = ft_get_env(temp, env);
	t[0] = 0;
	while (env_var[t[0]])
		pipe[f[0]++] = env_var[t[0]++];
	return (free(temp), free(env_var), 0);
}
