/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: enorie <enorie@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/07 12:54:17 by enorie            #+#    #+#             */
/*   Updated: 2023/11/08 16:02:56 by enorie           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	if (size == 0)
		return (ft_strlen(src));
	while (dst[j] && j < size)
		j++;
	while (src[i] && i + j < size - 1)
	{
		dst[j + i] = src[i];
		i++;
	}
	while (src[i])
		i++;
	dst[j + i] = '\0';
	return (j + i);
}
