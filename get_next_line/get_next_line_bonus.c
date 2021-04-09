/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lelsweyr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/11 12:44:55 by lelsweyr          #+#    #+#             */
/*   Updated: 2020/11/17 18:34:48 by lelsweyr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

static char			*ft_rem(char **line, char **re, int fd)
{
	char			*p_re;

	p_re = NULL;
	if (re[fd])
		if ((p_re = ft_strchr(re[fd], '\n')))
		{
			*p_re = '\0';
			*line = ft_strdup(re[fd]);
			re[fd] = ft_strcpy(re[fd], p_re + 1);
		}
		else
		{
			*line = ft_strdup(re[fd]);
			free(re[fd]);
		}
	else
		*line = ft_strdup("");
	return (p_re);
}

static char			*ft_free(char **line, char *buf)
{
	char *tmp;

	tmp = *line;
	*line = ft_strjoin(*line, buf);
	free(tmp);
	return (*line);
}

int					get_next_line(int fd, char **line)
{
	char			*buf;
	char			*p_n;
	int				bytes_count;
	static char		*re[1024];

	buf = malloc((BUFFER_SIZE + 1) * sizeof(char));
	if (fd < 0 || BUFFER_SIZE < 0 || !line || read(fd, buf, 0) < 0 || !buf)
		return (-1);
	p_n = ft_rem(line, re, fd);
	while (!p_n && (bytes_count = read(fd, buf, BUFFER_SIZE)))
	{
		buf[bytes_count] = '\0';
		if ((p_n = ft_strchr(buf, '\n')))
		{
			*p_n = '\0';
			re[fd] = ft_strdup(p_n + 1);
		}
		*line = ft_free(line, buf);
	}
	free(buf);
	if (!(p_n))
		re[fd] = NULL;
	return ((p_n) ? 1 : 0);
}
