/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: enorie <enorie@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/13 13:05:56 by enorie            #+#    #+#             */
/*   Updated: 2024/03/23 11:42:18 by enorie           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <signal.h>
#include <stdio.h>
#include <strings.h>

extern int		g_signal;

void	ft_signal_value(int *last_return)
{
	if (g_signal != 0)
	{
		if (g_signal == SIGINT)
			*last_return = 130;
		else if (g_signal == SIGQUIT)
			*last_return = 131;
		else
			*last_return = 0;
		g_signal = 0;
	}
}

void	ft_sighandle(int sigcode)
{
	g_signal = sigcode;
	if (sigcode == SIGINT)
	{
		printf("\n");
		rl_replace_line("", 0);
		rl_on_new_line();
		rl_redisplay();
	}
}

void	ft_sighandle_process(int sigcode)
{
	g_signal = sigcode;
	if (sigcode == SIGQUIT)
		printf("Quit (core dumped)");
	printf("\n");
}

void	sig_init(void)
{
	signal(SIGINT, ft_sighandle);
	signal(SIGQUIT, SIG_IGN);
}
