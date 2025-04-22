/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ticouvre <ticouvre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/12 10:23:01 by ticouvre          #+#    #+#             */
/*   Updated: 2024/03/15 13:00:01 by ticouvre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_n(char *str)
{
	int	i;

	i = 0;
	if (str[i] == '-')
		i++;
	while (str[i] == 'n')
		i++;
	if (str[i] == '\0' && i > 0)
		return (1);
	return (0);
}

int	ft_echo(t_prompt *prompt, t_exec *exec)
{
	int	i;
	int	n;

	i = 1;
	n = 0;
	(void)exec;
	while (prompt->cmd[i])
	{
		if (!check_n(prompt->cmd[i]))
			break ;
		i++;
		n++;
	}
	if (i == n + 1 && prompt->cmd[i])
		printf("%s", prompt->cmd[i++]);
	while (prompt->cmd[i])
	{
		printf(" %s", prompt->cmd[i]);
		i++;
	}
	if (n == 0)
		printf("\n");
	return (0);
}
