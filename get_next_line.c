/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: szemmour <szemmour@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/24 15:32:48 by szemmour          #+#    #+#             */
/*   Updated: 2024/11/30 16:51:16 by szemmour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

void	free_str(char **str)
{
	if (str && *str)
	{
		free(*str);
		*str = NULL;
	}
}

char	*read_line(int fd, char *buffer, char **left_str)
{
	int		read_size;
	char	*tmp;

	read_size = 1;
	while (read_size > 0)
	{
		read_size = read(fd, buffer, BUFFER_SIZE);
		if (read_size == -1)
			return (free_str(&buffer), free_str(left_str), NULL);
		buffer[read_size] = '\0';
		tmp = *left_str;
		*left_str = ft_strjoin(tmp, buffer);
		free_str(&tmp);
		if (ft_strchr(buffer, '\n') || read_size == 0)
			break ;
	}
	free_str(&buffer);
	return (*left_str);
}

char	*extract_line(char **left_str)
{
	char	*line;
	char	*tmp;
	char	*newline_pos;

	newline_pos = ft_strchr(*left_str, '\n');
	if (newline_pos)
	{
		line = ft_substr(*left_str, 0, newline_pos - *left_str + 1);
		tmp = *left_str;
		*left_str = ft_strdup(newline_pos + 1);
		free_str(&tmp);
	}
	else
	{
		line = ft_strdup(*left_str);
		free_str(left_str);
	}
	return (line);
}

char	*get_next_line(int fd)
{
	static char	*left_str;
	char		*buffer;
	char		*line;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	buffer = malloc(BUFFER_SIZE + 1);
	if (!buffer)
		return (NULL);
	if (!left_str)
		left_str = ft_strdup("");
	if (!read_line(fd, buffer, &left_str))
		return (NULL);
	if (!*left_str)
		return (free_str(&left_str), NULL);
	line = extract_line(&left_str);
	return (line);
}
