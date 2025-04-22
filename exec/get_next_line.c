/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ticouvre <ticouvre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/13 15:56:48 by enorie            #+#    #+#             */
/*   Updated: 2024/02/08 12:16:56 by ticouvre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/get_next_line.h"

char	*ft_free(char *s)
{
	free(s);
	return (NULL);
}

char	*ft_fill_str(int fd, char *rstr)
{
	char	*buffer;
	int		bytes;

	buffer = malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!buffer)
		return (NULL);
	bytes = 1;
	while (!checkstr(rstr))
	{
		bytes = read(fd, buffer, BUFFER_SIZE);
		if (bytes == 0)
			break ;
		if (bytes == -1)
			return (ft_free(buffer));
		buffer[bytes] = '\0';
		rstr = ft_strjoin_gnl(rstr, buffer);
		if (!rstr)
			return (ft_free(buffer));
	}
	free(buffer);
	return (rstr);
}

char	*ft_trim(char *rstr)
{
	char	*result;
	int		i;

	i = 0;
	while (rstr[i] && rstr[i] != '\n')
		i++;
	if (rstr[i] && rstr[i] == '\n')
		i++;
	result = malloc(sizeof(char) * (i + 1));
	if (!result)
		return (NULL);
	i = 0;
	while (rstr[i] && rstr[i] != '\n')
	{
		result[i] = rstr[i];
		i++;
	}
	if (rstr[i] && rstr[i] == '\n')
	{
		result[i] = rstr[i];
		i++;
	}
	result[i] = '\0';
	return (result);
}

void	ft_whats_left(char *rstr, char *reste)
{
	int		i;
	int		j;

	i = 0;
	j = 0;
	while (reste[i])
		reste[i++] = '\0';
	i = 0;
	while (rstr[i] && rstr[i] != '\n')
		i++;
	if (!rstr[i])
		return ;
	i++;
	while (rstr[i])
		reste[j++] = rstr[i++];
	reste[j] = '\0';
}

char	*get_next_line(int fd)
{
	char		*result;
	char		*tmp;
	static char	rstr[BUFFER_SIZE];

	tmp = NULL;
	if (rstr[0])
	{
		tmp = ft_strdup_gnl(rstr);
		if (!tmp)
			return (NULL);
	}
	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	tmp = ft_fill_str(fd, tmp);
	if (!tmp || !tmp[0])
		return (NULL);
	result = ft_trim(tmp);
	if (!result)
	{
		free(tmp);
		return (NULL);
	}
	ft_whats_left(tmp, rstr);
	free(tmp);
	return (result);
}
