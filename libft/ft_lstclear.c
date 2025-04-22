/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: enorie <enorie@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/09 17:06:16 by enorie            #+#    #+#             */
/*   Updated: 2023/11/09 17:19:14 by enorie           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void*))
{
	t_list	*t;

	if (!del || !lst || !*lst)
		return ;
	while (lst && *lst)
	{
		t = (*lst)->next;
		ft_lstdelone((*lst), (*del));
		(*lst) = t;
	}
}
