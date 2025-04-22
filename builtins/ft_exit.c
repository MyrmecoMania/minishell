/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ticouvre <ticouvre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/27 12:18:38 by ticouvre          #+#    #+#             */
/*   Updated: 2024/03/21 12:58:37 by ticouvre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_numeric(char *str)
{
	int	i;

	i = 0;
	if (str[i] == '-' || str[i] == '+')
		i++;
	while (str[i])
	{
		if (!(str[i] >= '0' && str[i] <= '9'))
			return (1);
		i++;
	}
	return (0);
}

unsigned long long	ft_atoull(const char *nbr)
{
	int					i;
	unsigned long long	r;
	int					s;

	i = 0;
	r = 0;
	s = 1;
	while ((nbr[i] >= 9 && nbr[i] <= 13) || nbr[i] == ' ')
		i++;
	if (nbr[i] == '-' || nbr[i] == '+')
	{
		if (nbr[i] == '-')
			s *= -1;
		i++;
	}
	while (nbr[i] > 47 && nbr[i] < 58)
	{
		r = r * 10 + (nbr[i] - '0');
		i++;
	}
	return (r * s);
}

int	ft_condition(t_prompt *prompt)
{
	if ((prompt->cmd[1] && check_numeric(prompt->cmd[1])) || (prompt->cmd[1]
			&& (ft_atoull(prompt->cmd[1]) > 9223372036854775807
				|| (ft_strlen(prompt->cmd[1]) > 19))))
		return (1);
	return (0);
}

int	ft_exit(t_prompt *prompt, int i)
{
	if (ft_size(prompt) != 1)
		return (0);
	if (i == 0 && ft_size(prompt) == 1)
		printf("exit\n");
	if (ft_condition(prompt))
	{
		ft_putstr_fd("exit: ", 2);
		ft_putstr_fd(prompt->cmd[1], 2);
		ft_putstr_fd(": numeric argument required\n", 2);
		return (2);
	}
	if (prompt->tcmd > 2)
	{
		ft_putstr_fd("exit: too many arguments\n", 2);
		return (257);
	}
	if (prompt->tcmd == 2 && (ft_atoi(prompt->cmd[1]) >= 0
			&& ft_atoi(prompt->cmd[1]) <= 255))
		return (ft_atoi(prompt->cmd[1]));
	if (prompt->tcmd == 1)
		return (0);
	if (prompt->tcmd == 2)
		return (ft_atoi(prompt->cmd[1]) % 256);
	return (0);
}
