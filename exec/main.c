/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ticouvre <ticouvre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/29 17:20:34 by ticouvre          #+#    #+#             */
/*   Updated: 2024/03/23 10:55:12 by ticouvre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_write_parse_error(int nbr, int *last_return)
{
	*last_return = 2;
	if (nbr == 1)
		return (ft_putstr_fd(ERROR_MSG1, 2));
	else if (nbr == 2)
		return (ft_putstr_fd(ERROR_MSG2, 2));
	else if (nbr == 3)
		return (ft_putstr_fd(ERROR_MSG3, 2));
	else if (nbr == 4)
		return (ft_putstr_fd(ERROR_MSG4, 2));
	else if (nbr == 5)
		return (ft_putstr_fd(ERROR_MSG5, 2));
	else if (nbr == 6)
		return (ft_putstr_fd(ERROR_MSG6, 2));
}

int	ft_cmp(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		while (str[i] && str[i] != '|')
			i++;
		if (str[i] && str[i] == '|' && !str[i + 1])
			return (ft_putstr_fd(ERROR_MSG1, 2), 1);
		if (str[i] && str[i] == '|')
			i++;
		while (str[i] && (str[i] == ' ' || (str[i] >= 9 && str[i] <= 13)))
			i++;
		if (str[i] && str[i] == '|')
			return (ft_putstr_fd(ERROR_MSG1, 2), 1);
	}
	return (0);
}

int	ft_parse_and_exec(char *str, int *last_return, t_exec *exec)
{
	t_prompt	*prompt;

	prompt = NULL;
	if (!(ft_check_parsed_pipes(str) || ft_check_prompt(str) || ft_cmp(str)))
	{
		prompt = ft_parse(str, *last_return, exec->env);
		if (!prompt)
			return (free(str), rl_clear_history(), 1);
		if (!prompt->error)
		{
			exec->pid = malloc(sizeof(pid_t) * (ft_size(prompt)));
			if (!exec->pid)
				return (free(str), free(exec->pid), ffa(prompt, NULL, NULL), 1);
			*last_return = exece(prompt, exec);
			if (*last_return == ERROR_MALLOC)
				return (free(str), free(exec->pid), ffa(prompt, NULL, NULL), 1);
			free(exec->pid);
		}
		else
			ft_write_parse_error(prompt->error, last_return);
	}
	else
		*last_return = 2;
	ffa(prompt, NULL, NULL);
	return (0);
}

int	ft_infinite_readline(int *last_return, t_exec *exec)
{
	char	*str;

	while (exec->exit)
	{
		sig_init();
		str = readline("minishell$ ");
		if (!str)
		{
			printf("exit\n");
			break ;
		}
		add_history(str);
		if (str[0])
		{
			ft_signal_value(last_return);
			if (ft_parse_and_exec(str, last_return, exec))
				return (-1);
		}
		free(str);
		str = NULL;
	}
	return (*last_return);
}

int	main(int ac, char *av[], char *env[])
{
	t_exec		*exec;
	char		**env_cpy;
	int			last_return;

	(void)ac;
	(void)av;
	if (!isatty(STDIN_FILENO))
		return (1);
	exec = malloc(sizeof(t_exec));
	exec->pipefd = NULL;
	exec->env = NULL;
	exec->pid = NULL;
	exec->exit = 1;
	if (!exec)
		return (1);
	env_cpy = ft_rep_env_var(env);
	if (!env_cpy)
		return (free(exec), 1);
	exec->env = env_cpy;
	last_return = 0;
	if (ft_shlvl(exec) == ERROR_MALLOC)
		return (free_tab(exec->env), free(exec), 1);
	if (ft_infinite_readline(&last_return, exec) < 0)
		return (ft_free_exec(exec), rl_clear_history(), last_return);
	return (ft_free_exec(exec), rl_clear_history(), last_return);
}
