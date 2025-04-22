/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_env_var.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: enorie <enorie@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/08 23:07:16 by enorie            #+#    #+#             */
/*   Updated: 2024/03/23 12:53:03 by enorie           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_choose_env(char *str, int *r, char **env)
{
	char	*env_var;
	int		t;

	if (str[r[2]] == '$' && str[r[2] + 1] && str[r[2] + 1] == '?')
		ft_get_last_return_length(r[1], &r[2], &r[0]);
	else if (str[r[2]] == '$')
	{
		t = r[2] + 1;
		while (ft_check_conditions(str[t]))
			t++;
		env_var = malloc(sizeof(char) * (t - r[2] + 1));
		if (!env_var)
			return (1);
		t = 0;
		env_var[t++] = str[(r[2])++];
		while (ft_check_conditions(str[r[2]]))
			env_var[t++] = str[(r[2])++];
		env_var[t] = '\0';
		r[0] += ft_get_env_size(env_var, env);
		free(env_var);
	}
	while (ft_check_conditions(str[r[2]]))
		ft_increment(&r[2], &r[0]);
	return (0);
}

char	*ft_env_str(char *str, int *r, char **env)
{
	char	*final;

	while (str[r[2]])
	{
		if (ft_check_conditions2(str[r[2]], str[r[2] + 1]))
			ft_increment(&r[2], &r[0]);
		ft_pass_quotes_env_var(str, r);
		if (ft_choose_env(str, r, env))
			return (NULL);
	}
	final = malloc(sizeof(char) * (r[0] + 1));
	if (!final)
		return (NULL);
	return (final);
}

int	ft_cpy_choose_env(char *s, char *str, int *r, char **env)
{
	char	*env_var;
	char	*temp;
	int		t;

	if (s[r[2]] == '$' && s[r[2] + 1] && s[r[2] + 1] == '?')
		ft_cpy_env_var(str, r, &r[2]);
	else if (s[r[2]] == '$')
	{
		t = r[2] + 1;
		while (ft_conditions(s[t]))
			t++;
		env_var = malloc(sizeof(char) * (t - r[2] + 1));
		if (!env_var)
			return (1);
		ft_cpy_env_var_name(s, env_var, r);
		temp = ft_get_env(env_var, env);
		if (!temp)
			return (free(env_var), 1);
		free(env_var);
		t = 0;
		while (temp[t])
			str[r[0]++] = temp[t++];
		free(temp);
	}
	return (0);
}

int	ft_cpy_env_str(char *src, char *str, int *r, char **env)
{
	while (src[r[2]])
	{
		if (ft_check_conditions2(src[r[2]], src[r[2] + 1]))
			str[r[0]++] = src[(r[2])++];
		if (src[r[2]] == '\'')
		{
			str[r[0]++] = src[(r[2])++];
			while (src[r[2]] != '\'')
				str[r[0]++] = src[(r[2])++];
			str[r[0]++] = src[(r[2])++];
		}
		if (src[r[2]] == '\"')
		{
			str[r[0]++] = src[(r[2])++];
			while (src[r[2]] != '\"')
				str[r[0]++] = src[(r[2])++];
			str[r[0]++] = src[(r[2])++];
		}
		if (ft_cpy_choose_env(src, str, r, env))
			return (1);
		while (ft_check_conditions(src[r[2]]))
			str[r[0]++] = src[(r[2])++];
	}
	return (0);
}

int	ft_get_env_var(char **str, int j, int last_return, char **env)
{
	int		r[3];
	char	*final;

	r[2] = 0;
	r[0] = 0;
	r[1] = last_return;
	final = ft_env_str(str[j], r, env);
	if (!final)
		return (1);
	r[0] = 0;
	r[2] = 0;
	if (ft_cpy_env_str(str[j], final, r, env))
		return (free(final), 1);
	final[r[0]] = '\0';
	free(str[j]);
	str[j] = final;
	return (0);
}
