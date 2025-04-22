/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: enorie <enorie@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/09 17:33:06 by enorie            #+#    #+#             */
/*   Updated: 2023/11/10 17:21:10 by enorie           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*r;
	t_list	*t;

	r = NULL;
	if (!(*f) || !(*del))
		return (NULL);
	while (lst)
	{
		t = ft_lstnew((*f)(lst->content));
		if (!t)
		{
			while (r)
			{
				t = r->next;
				ft_lstdelone(r, (*del));
				r = t;
			}
			return (NULL);
		}
		ft_lstadd_back(&r, t);
		lst = lst->next;
	}
	return (r);
}
