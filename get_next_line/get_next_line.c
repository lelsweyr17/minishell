/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lelsweyr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/11 12:44:55 by lelsweyr          #+#    #+#             */
/*   Updated: 2020/11/11 12:44:59 by lelsweyr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static char			*ft_rem(char **line, char *re)
{
	char			*p_re;

	p_re = NULL;
	if (re)
		if ((p_re = ft_strchr(re, '\n')))
		{
			*p_re = '\0';
			*line = ft_strdup(re);
			re = ft_strcpy(re, p_re + 1);
		}
		else
		{
			*line = ft_strdup(re);
			free(re);
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
	static char		*re;

	buf = malloc((BUFFER_SIZE + 1) * sizeof(char));
	if (fd < 0 || BUFFER_SIZE < 0 || !line || read(fd, buf, 0) < 0 || !buf)
		return (-1);
	p_n = ft_rem(line, re);
	while (!p_n && (bytes_count = read(fd, buf, BUFFER_SIZE)))
	{
		buf[bytes_count] = '\0';
		if ((p_n = ft_strchr(buf, '\n')))
		{
			*p_n = '\0';
			re = ft_strdup(p_n + 1);
		}
		*line = ft_free(line, buf);
	}
	free(buf);
	if (!(p_n))
		re = NULL;
	return ((p_n) ? 1 : 0);
}
