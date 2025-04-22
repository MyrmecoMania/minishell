/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_env_var_utils2.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: enorie <enorie@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/11 11:50:58 by enorie            #+#    #+#             */
/*   Updated: 2024/03/22 14:05:22 by enorie           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_cpy_env_var_name(char *src, char *env_var, int *r)
{
	int	t;

	t = 0;
	env_var[t++] = src[(r[2])++];
	while (ft_check_conditions(src[r[2]]))
		env_var[t++] = src[(r[2])++];
	env_var[t] = '\0';
}

int	ft_check_conditions(char c)
{
	if (c && (ft_isalnum(c) || c == '?'))
		return (1);
	return (0);
}

char	*ft_no_env(char *str)
{
	char	*temp;

	temp = malloc(sizeof(char) * 2);
	if (!temp)
		return (NULL);
	if (str[0] && !str[1])
	{
		temp[0] = '$';
		temp[1] = '\0';
	}
	else
		temp[0] = '\0';
	return (temp);
}

int	ft_which_len(char *env, char *str)
{
	if (ft_envlen(env) > (int)ft_strlen(str + 1))
		return (ft_envlen(env));
	else
		return (ft_strlen(str + 1));
}

int	ft_conditions(char c)
{
	if (c && c != '\"' && c != '\'' && c != ' ' && c != '$')
		return (1);
	return (0);
}
