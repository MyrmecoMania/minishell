/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: enorie <enorie@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/08 13:55:05 by enorie            #+#    #+#             */
/*   Updated: 2023/11/09 16:28:03 by enorie           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	c_number(int n)
{
	int		i;
	long	ln;

	i = 0;
	ln = n;
	if (ln < 0)
	{
		i++;
		ln *= -1;
	}
	if (ln == 0)
		return (1);
	while (ln > 0)
	{
		ln /= 10;
		i++;
	}
	return (i);
}

char	*ft_itoa(int n)
{
	char	*r;
	int		c;
	long	ln;

	ln = n;
	c = c_number(ln);
	r = malloc(sizeof(char) * (c + 1));
	if (!r)
		return (NULL);
	r[c] = '\0';
	if (n < 0)
	{
		r[0] = '-';
		ln *= -1;
	}
	if (ln == 0)
		r[0] = '0';
	while (ln > 0)
	{
		r[c - 1] = (ln % 10) + '0';
		ln /= 10;
		c--;
	}
	return (r);
}
