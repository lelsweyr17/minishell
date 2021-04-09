/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lelsweyr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/11 16:23:39 by lelsweyr          #+#    #+#             */
/*   Updated: 2020/11/11 16:23:42 by lelsweyr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char				*ft_strcpy(char *dst, const char *src)
{
	int				i;
	unsigned char	*d;
	unsigned char	*s;
	int				dstsize;

	i = 0;
	if (!src)
		return (0);
	s = (unsigned char *)src;
	d = (unsigned char *)dst;
	dstsize = ft_strlen((char *)s);
	while (s[i] && i < dstsize)
	{
		d[i] = s[i];
		i++;
	}
	d[i] = '\0';
	return (dst);
}

int					ft_strlen(char *str)
{
	int i;

	i = 0;
	while (str[i] != '\0')
		i++;
	return (i);
}

char				*ft_strjoin(char const *s1, char const *s2)
{
	int				i;
	int				j;
	char			*res;
	int				size1;
	int				size2;

	i = -1;
	j = -1;
	if (!s1 || !s2)
		return (NULL);
	size1 = ft_strlen((char *)s1);
	size2 = ft_strlen((char *)s2);
	res = (char *)malloc((size1 + size2 + 1) * sizeof(char));
	if (!res)
		return (NULL);
	while (i++ < (size1 - 1))
		res[i] = s1[i];
	while (j++ < (size2 - 1))
		res[i + j] = s2[j];
	res[i + j] = '\0';
	return (res);
}

char				*ft_strchr(const char *s, int c)
{
	int				i;
	unsigned char	sym;
	char			*a;

	i = 0;
	a = (char *)s;
	sym = (unsigned char)c;
	if (sym == '\0')
	{
		while (a[i] != '\0')
			i++;
		return (&a[i]);
	}
	while (a[i] != '\0')
	{
		if (a[i] == sym)
			return (&a[i]);
		else
			i++;
	}
	return (NULL);
}

char				*ft_strdup(const char *s1)
{
	int				i;
	char			*s;
	int				len;

	i = 0;
	len = ft_strlen((char *)s1);
	if (!s1)
		return (NULL);
	s = (char *)malloc((len + 1) * sizeof(char));
	if (!s)
		return (NULL);
	while (i < len)
	{
		s[i] = s1[i];
		i++;
	}
	s[i] = '\0';
	return (s);
}
