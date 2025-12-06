/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arochd <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/12 13:51:39 by arochd            #+#    #+#             */
/*   Updated: 2025/11/14 15:06:27 by arochd           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

static char	*remain_read(int fd, char *remain)
{
	char	*buf;
	int		nb_read;
	char	*temp;

	buf = malloc((size_t)BUFFER_SIZE + 1);
	if (!buf)
		return (free(remain), NULL);
	nb_read = 1;
	while (nb_read > 0 && (ft_strchr(remain, '\n') == -1))
	{
		nb_read = read(fd, buf, BUFFER_SIZE);
		if (nb_read < 0)
			return (free(buf), free(remain), NULL);
		buf[nb_read] = '\0';
		temp = remain;
		remain = ft_strjoin(temp, buf);
		free(temp);
		if (!remain)
			return (free(buf), NULL);
	}
	free(buf);
	return (remain);
}

static char	*line_extracter(char *str)
{
	char	*line;
	int		index;

	if (!str || !*str)
		return (NULL);
	index = ft_strchr(str, '\n');
	if (index == -1)
		line = ft_strdup(str);
	else
		line = ft_substr(str, 0, index + 1);
	return (line);
}

static char	*remained(char *str)
{
	char	*remain;
	int		index;

	index = ft_strchr(str, '\n');
	if (index == -1)
	{
		free(str);
		return (NULL);
	}
	remain = ft_substr(str, index + 1, ft_strlen(str) - (index + 1));
	free(str);
	return (remain);
}

char	*get_next_line(int fd)
{
	static char		*remain[1024];
	char			*line;

	if (fd < 0 || fd >= 1024 || BUFFER_SIZE <= 0)
		return (NULL);
	remain[fd] = remain_read(fd, remain[fd]);
	if (!remain[fd])
		return (NULL);
	line = line_extracter(remain[fd]);
	remain[fd] = remained(remain[fd]);
	return (line);
}
