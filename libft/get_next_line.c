/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmarsha <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/14 15:00:01 by cmarsha           #+#    #+#             */
/*   Updated: 2021/01/24 14:52:14 by cmarsha          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static	char	*cashcheck(char *cash, char **line)
{
	char				*np;
	int					i;

	i = 0;
	np = NULL;
	*line = ft_strdup("");
	if (cash)
	{
		if ((np = ft_strchr(cash, '\n')))
		{
			*np = '\0';
			free(*line);
			*line = ft_strdup(cash);
			ft_strcpy(cash, ++np);
		}
		else
		{
			free(*line);
			*line = ft_strdup(cash);
			while (cash[i])
				cash[i++] = '\0';
		}
	}
	return (np);
}

static	char	*ft_freetmp(char **line, char *ln)
{
	char				*tmp;

	tmp = ft_strjoin(*line, ln);
	free(*line);
	*line = tmp;
	return (*line);
}

int				get_next_line(int fd, char **line)
{
	int					ret;
	char				ln[BUFFER_SIZE + 1];
	char				*np;
	static	char		cash[1024][BUFFER_SIZE + 1];

	if (!line || fd < 0 || read(fd, ln, 0) < 0 || BUFFER_SIZE < 1)
		return (-1);
	np = cashcheck(cash[fd], line);
	while ((!np) && (ret = read(fd, ln, BUFFER_SIZE)) > 0)
	{
		ln[ret] = '\0';
		if ((np = ft_strchr(ln, '\n')))
		{
			*np = '\0';
			ft_strcpy(cash[fd], ++np);
		}
		*line = ft_freetmp(line, ln);
	}
	return (ret || np ? 1 : 0);
}
