/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: enorie <enorie@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/08 13:13:29 by enorie            #+#    #+#             */
/*   Updated: 2023/11/09 16:28:22 by enorie           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	free_tab(char **tab, size_t k, size_t max)
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

static int	fill_tab(char **tab, const char	*s, char c, int count)
{
	int	i;
	int	j;
	int	t;

	i = 0;
	j = 0;
	while (i < count)
	{
		t = 0;
		while (s[j] == c)
			j++;
		while (s[j] != c && s[j])
		{
			t++;
			j++;
		}
		tab[i] = malloc(sizeof(char) * (t + 1));
		if (!tab[i])
		{
			free_tab(tab, i, count);
			return (1);
		}
		i++;
	}
	return (0);
}

static int	count_s(char const *s, char c)
{
	int	i;
	int	count;

	i = 0;
	count = 1;
	while (s[i] == c && s[i])
		i++;
	if (!s[i])
		return (0);
	while (s[i])
	{
		if (s[i] == c)
		{
			if (s[i + 1] != c && s[i + 1] != '\0')
				count++;
		}
		i++;
	}
	return (count);
}

static char	**create_tab(char const *s, char c)
{
	char	**tab;
	int		count;

	count = count_s(s, c);
	tab = malloc(sizeof(char *) * (count + 1));
	if (!tab)
		return (NULL);
	if (fill_tab(tab, s, c, count))
		return (NULL);
	tab[count] = 0;
	return (tab);
}

char	**ft_split(char const *s, char c)
{
	char	**tab;
	int		i;
	int		j;
	int		t;
	int		count;

	if (!s)
		return (NULL);
	tab = create_tab(s, c);
	if (!tab)
		return (NULL);
	i = 0;
	j = 0;
	count = count_s(s, c);
	while (i < count)
	{
		t = 0;
		while (s[j] == c)
			j++;
		while (s[j] != c && s[j])
			tab[i][t++] = s[j++];
		tab[i][t] = '\0';
		i++;
	}
	return (tab);
}
