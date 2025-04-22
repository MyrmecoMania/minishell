/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: enorie <enorie@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/08 11:55:50 by enorie            #+#    #+#             */
/*   Updated: 2023/11/09 15:18:49 by enorie           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	check_charset(char a, char const *set)
{
	size_t	i;

	i = 0;
	while (set[i])
	{
		if (a == set[i])
			return (1);
		i++;
	}
	return (0);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	size_t	s;
	size_t	e;
	size_t	i;
	char	*r;

	if (!s1)
		return (NULL);
	s = 0;
	i = 0;
	e = ft_strlen(s1);
	while (check_charset(s1[s], set) && s1[s])
		s++;
	while (e > s && check_charset(s1[e - 1], set))
		e--;
	r = malloc(sizeof(char) * (e - s + 1));
	if (!r)
		return (NULL);
	while (s < e)
		r[i++] = s1[s++];
	r[i] = '\0';
	return (r);
}
