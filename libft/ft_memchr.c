/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: enorie <enorie@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/06 16:31:03 by enorie            #+#    #+#             */
/*   Updated: 2023/11/09 13:35:06 by enorie           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	size_t			i;
	unsigned char	*scast;
	unsigned char	ccast;

	ccast = (unsigned char)c;
	scast = (unsigned char *)s;
	i = 0;
	while (i < n)
	{
		if (scast[i] == ccast)
			return ((&scast[i]));
		i++;
	}
	return (NULL);
}
