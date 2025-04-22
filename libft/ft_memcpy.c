/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: enorie <enorie@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/06 14:36:35 by enorie            #+#    #+#             */
/*   Updated: 2023/11/09 13:39:34 by enorie           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	size_t			i;
	char			*dcast;
	char			*scast;

	i = 0;
	if (!dest && !src)
		return (NULL);
	dcast = (char *)dest;
	scast = (char *)src;
	while (i < n)
	{
		dcast[i] = scast[i];
		i++;
	}
	return (dest);
}
