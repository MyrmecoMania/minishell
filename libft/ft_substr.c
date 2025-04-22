/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: enorie <enorie@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/07 14:42:45 by enorie            #+#    #+#             */
/*   Updated: 2023/11/09 15:25:58 by enorie           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	unsigned int	i;
	char			*r;

	if (!s)
		return (NULL);
	if (start > ft_strlen(s))
	{
		r = malloc(sizeof(char));
		if (!r)
			return (NULL);
		r[0] = '\0';
		return (r);
	}
	i = start;
	while (s[i] && (i - start) < (unsigned int)len)
		i++;
	r = malloc(sizeof(char) * ((i - start) + 1));
	if (!r)
		return (NULL);
	i = 0;
	while (s[start] && i < (unsigned int)len)
		r[i++] = s[start++];
	r[i] = '\0';
	return (r);
}
