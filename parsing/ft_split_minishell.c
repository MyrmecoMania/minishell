/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_minishell.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: enorie <enorie@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/12 16:04:13 by enorie            #+#    #+#             */
/*   Updated: 2024/03/15 13:33:34 by enorie           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	ft_free_tab(char **tab, size_t k, size_t max)
{
	size_t	i;

	i = 0;
	while (i != k)
	{
		free(tab[i]);
	}
	free(tab[max]);
	free(tab);
}

static int	fill_tab(char **tab, const char	*s, char c, int *count)
{
	int	i;

	i = 0;
	while (s[count[1]] && s[count[1]] == c)
		count[1]++;
	while (s[count[1]] && s[count[1]] != c)
	{
		i += ft_pass_quotes(s, count[1]) - count[1];
		count[1] = ft_pass_quotes(s, count[1]);
		while (s[count[1]] && s[count[1]] != c && s[count[1]] != '\''
			&& s[count[1]] != '\"')
		{
			count[1]++;
			i++;
		}
	}
	tab[count[0]] = malloc(sizeof(char) * (i + 1));
	if (!tab[count[0]])
		return (1);
	return (0);
}

static int	count_s(char const *s, char c)
{
	int	i;
	int	count;

	i = 0;
	count = 1;
	while (s[i] && s[i] == c)
		i++;
	if (!s[i])
		return (0);
	while (s[i])
	{
		if (s[i] == '\'' || s[i] == '\"')
			i = ft_pass_quotes(s, i);
		else if (s[i] && s[i] == c)
		{
			if (s[i + 1] && s[i + 1] != c)
				count++;
			i++;
		}
		else
			i++;
	}
	return (count);
}

static char	**create_tab(char const *s, char c)
{
	char	**tab;
	int		count;
	int		i[2];

	count = count_s(s, c);
	tab = malloc(sizeof(char *) * (count + 1));
	if (!tab)
		return (NULL);
	tab[count] = NULL;
	i[0] = 0;
	i[1] = 0;
	while (i[0] < count)
	{
		if (fill_tab(tab, s, c, i))
			return (ft_free_tab(tab, i[0], count), NULL);
		i[0]++;
	}
	return (tab);
}

char	**ft_split_minishell(char const *s, char c)
{
	char	**tab;
	int		i[3];

	if (!s)
		return (NULL);
	tab = create_tab(s, c);
	if (!tab)
		return (NULL);
	i[0] = 0;
	i[1] = 0;
	i[2] = count_s(s, c);
	while (i[0] < i[2])
	{
		ft_fill_minishell_split(s, c, &i[1], tab[i[0]]);
		i[0]++;
	}
	return (tab);
}
