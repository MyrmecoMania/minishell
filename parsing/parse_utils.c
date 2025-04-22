/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: enorie <enorie@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/01 14:09:52 by enorie            #+#    #+#             */
/*   Updated: 2024/03/19 15:32:10 by enorie           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_count_quotes(char *str, int *i, int *j)
{
	while (str[*i] && (str[*i] == ' ' || (str[*i] >= 9 && str[*i] <= 13)))
		(*i)++;
	if (str[*i] == '\'')
	{
		ft_increment(i, j);
		while (str[*i] != '\'')
			ft_increment(i, j);
		ft_increment(i, j);
	}
	if (str[*i] == '\"')
	{
		ft_increment(i, j);
		while (str[*i] != '\"')
			ft_increment(i, j);
		ft_increment(i, j);
	}
	while (str[*i] && !(str[*i] == ' ' || (str[*i] >= 9 && str[*i] <= 13))
		&& str[*i] != '<' && str[*i] != '>' && str[*i] != '\''
		&& str[*i] != '\"')
		ft_increment(i, j);
}

int	ft_count_new_str(char *str)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (str[i])
	{
		ft_count_quotes(str, &i, &j);
		if (str[i] && (str[i] == '>' || str[i] == '<') && i > 0
			&& str[i - 1] != '<' && str[i - 1] != '>')
		{
			i++;
			j += 2;
		}
		else if (str[i] && str[i] != '\'' && str[i] != '\"')
			ft_increment(&i, &j);
		if (str[i] && (str[i] == ' ' || (str[i] >= 9 && str[i] <= 13))
			&& (str[i - 1] && !(str[i - 1] == ' ' || (str[i - 1] >= 9
						&& str[i - 1] <= 13)))
			&& ft_nextchar(str, i, str[i - 1]))
			j++;
	}
	return (j);
}

void	ft_cpy_quotes(char *str, int *i, int *j, char *r)
{
	if (str[*i] == '\"')
	{
		r[(*j)++] = str[(*i)++];
		while (str[*i] != '\"')
			r[(*j)++] = str[(*i)++];
		r[(*j)++] = str[(*i)++];
	}
	while (str[*i] && !(str[*i] == ' ' || (str[*i] >= 9 && str[*i] <= 13))
		&& str[*i] != '<' && str[*i] != '>' && str[*i] != '\''
		&& str[*i] != '\"')
		r[(*j)++] = str[(*i)++];
	if ((str[*i] == '>' || str[*i] == '<') && *i > 0 && str[*i - 1] != '<'
		&& str[*i - 1] != '>')
	{
		r[(*j)++] = ' ';
		r[(*j)++] = str[(*i)++];
	}
	else if (str[*i] && str[*i] != '\'' && str[*i] != '\"')
		r[(*j)++] = str[(*i)++];
	if (str[*i] && (str[*i] == ' ' || (str[*i] >= 9 && str[*i] <= 13))
		&& (str[*i - 1] && !(str[*i - 1] == ' ' || (str[*i - 1] >= 9
					&& str[*i - 1] <= 13))) && ft_nextchar(str, *i, r[*j - 1]))
		r[(*j)++] = ' ';
}

char	*ft_trim_prompt(char *str)
{
	char	*r;
	int		i;
	int		j;

	r = malloc(sizeof(char) * (ft_count_new_str(str) + 1));
	if (!r)
		return (NULL);
	r[0] = 'a';
	i = 0;
	j = 0;
	while (str[i])
	{
		while (str[i] && (str[i] == ' ' || (str[i] >= 9 && str[i] <= 13)))
			i++;
		if (str[i] == '\'')
		{
			r[j++] = str[i++];
			while (str[i] != '\'')
				r[j++] = str[i++];
			r[j++] = str[i++];
		}
		ft_cpy_quotes(str, &i, &j, r);
	}
	r[j] = '\0';
	return (r);
}

int	ft_isheredoc(char *str)
{
	if (str[0] == '<' && str[1] == '<')
		return (1);
	return (0);
}
