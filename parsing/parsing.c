/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: enorie <enorie@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/29 18:54:15 by enorie            #+#    #+#             */
/*   Updated: 2024/03/23 12:33:58 by enorie           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_parse_pipe(char *str, t_prompt *cmd)
{
	if (str[0] == '<' || str[0] == '>')
	{
		if (ft_parse_file(str, cmd))
			return (1);
	}
	else
	{
		cmd->cmd[cmd->tcmd] = ft_strdup(str);
		if (!cmd->cmd[cmd->tcmd])
			return (1);
		cmd->tcmd += 1;
	}
	return (0);
}

int	ft_malloc_struct(char **parsed_pipe, t_prompt *cmd)
{
	int	i[4];

	i[0] = 0;
	i[1] = 0;
	i[2] = 0;
	while (parsed_pipe[i[0]])
	{
		if (parsed_pipe[i[0]][0] == '>' || parsed_pipe[i[0]][0] == '<')
		{
			if (parsed_pipe[i[0]][0] == '<' && parsed_pipe[i[0]][1] == '<')
				i[1]++;
		}
		else
			i[2]++;
		i[0]++;
	}
	cmd->cmd = malloc(sizeof(char *) * (i[2] + 1));
	if (!cmd->cmd)
		return (1);
	cmd->here_doc = malloc(sizeof(char *) * (i[1] + 1));
	if (!cmd->here_doc)
		return (1);
	return (0);
}

int	ft_choose(char **parsed_pipe, int *j, t_prompt *cmd, int last_return)
{
	int	i;

	while (parsed_pipe[*j])
	{
		if (!ft_is_present(parsed_pipe[*j], '$')
			&& !ft_isheredoc(parsed_pipe[*j]))
			if (ft_get_env_var(parsed_pipe, *j, last_return, cmd->env))
				return (1);
		if (ft_parse_pipe(parsed_pipe[(*j)++], cmd))
			return (1);
		i = -1;
		while (++i < cmd->tcmd)
		{
			if (!ft_is_present(cmd->cmd[i], '\'')
				|| !ft_is_present(cmd->cmd[i], '\"'))
				if (ft_parse_quotes(cmd->cmd, i, last_return, cmd->env))
					return (1);
		}
	}
	return (0);
}

int	ft_get_prompt(t_prompt **cmds, char **pipes, int lr, char **env)
{
	int			i[2];
	char		**pp;
	t_prompt	*cmd;

	i[0] = -1;
	while (pipes[++i[0]])
	{
		i[1] = 0;
		cmd = ft_create_prompt(cmds, env);
		if (!cmd)
			return (1);
		pp = ft_split_minishell(pipes[i[0]], ' ');
		if (!pp)
			return (ffa(cmd, NULL, NULL), 1);
		if (ft_malloc_struct(pp, cmd) || ft_choose(pp, &i[1], cmd, lr))
			return (ffa(cmd, pp, NULL), 1);
		if (cmd->tcmd > 0 && cmd->cmd[0] && ft_get_the_path(cmd, env, pp))
			return (1);
		cmd->cmd[cmd->tcmd] = NULL;
		cmd->here_doc[cmd->there_doc] = NULL;
		cmd->error = ft_check_pipes(pp, pipes, i[0]);
		ffa(NULL, pp, NULL);
	}
	return (0);
}

t_prompt	*ft_parse(char *str, int last_return, char **env)
{
	char		*ligne;
	char		**pipes;
	t_prompt	*cmds;

	cmds = NULL;
	ligne = ft_trim_prompt(str);
	if (!ligne)
		return (NULL);
	pipes = ft_split_minishell(ligne, '|');
	if (!pipes)
		return (NULL);
	if (ft_get_prompt(&cmds, pipes, last_return, env))
		return (free(ligne), ffa(NULL, pipes, NULL), NULL);
	ft_error_climber(&cmds);
	free(ligne);
	return (ffa(NULL, pipes, NULL), cmds);
}
