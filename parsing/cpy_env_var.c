/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cpy_env_var.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: enorie <enorie@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/20 13:02:00 by enorie            #+#    #+#             */
/*   Updated: 2024/03/23 12:53:32 by enorie           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	ft_free_tab(char **tab, size_t k)
{
	size_t	i;

	i = 0;
	while (i != k)
	{
		free(tab[i]);
	}
	free(tab);
}

int	ft_tab_size(char **tab)
{
	int	i;

	i = 0;
	while (tab[i])
		i++;
	return (i);
}

char	**ft_rep_env_var(char **env)
{
	char	**r;
	int		i;
	int		t;

	t = ft_tab_size(env);
	i = 0;
	r = malloc(sizeof(char *) * (t + 1));
	if (!r)
		return (NULL);
	while (i < t)
	{
		r[i] = ft_strdup(env[i]);
		if (!r[i])
			return (ft_free_tab(r, i), NULL);
		i++;
	}
	r[i] = NULL;
	return (r);
}
