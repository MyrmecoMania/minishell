/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: enorie <enorie@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/23 12:12:28 by enorie            #+#    #+#             */
/*   Updated: 2024/03/23 12:29:09 by enorie           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_strdup_x(char *s)

{
	size_t		len;
	size_t		i;
	char		*r;

	i = 0;
	len = ft_strlen(s);
	r = malloc(len * sizeof(char));
	if (!r)
		return (NULL);
	len = 0;
	while (s[i] != '=')
	{
		if (s[i] != '+')
			r[len++] = s[i];
		i++;
	}
	while (s[i])
		r[len++] = s[i++];
	r[len] = '\0';
	return (r);
}

int	ft_is_present_x(char *str, char c)
{
	int	i;

	i = 0;
	while (str[i] != '=')
	{
		if (str[i] == c)
			return (0);
		i++;
	}
	return (1);
}

void	ft_print_export_error(t_prompt *prompt, int *i)
{
	ft_putstr_fd("export: `", 2);
	ft_putstr_fd(prompt->cmd[i[2]++], 2);
	ft_putstr_fd("': not a valid identifier\n", 2);
}
