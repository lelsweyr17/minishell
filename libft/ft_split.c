/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lelsweyr <lelsweyr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/23 03:16:25 by student           #+#    #+#             */
/*   Updated: 2021/04/15 12:56:03 by lelsweyr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdio.h>

static int	ft_count(char const *s, char c)
{
	int	i;
	int	count;

	if (!s[0])
		return (0);
	i = 0;
	count = 0;
	while (s[i] && s[i] == c)
		i++;
	while (s[i])
	{
		if (s[i] == c)
		{
			count++;
			while (s[i] && s[i] == c)
				i++;
		}
		else
			i++;
	}
	if (s[i - 1] != c)
		count++;
	return (count);
}

static void	ft_len(char **str, int *str_len, char c)
{
	int	i;

	i = 0;
	*str += *str_len;
	*str_len = 0;
	while (**str && **str == c)
		(*str)++;
	while ((*str)[i])
	{
		if ((*str)[i] == c)
			return ;
		(*str_len)++;
		i++;
	}
}

static char	**ft_free(char **res)
{
	int	i;

	i = 0;
	while (res[i])
	{
		free(res[i]);
		i++;
	}
	free(res);
	return (NULL);
}

static void	ft_full(char *res, char *str, int len)
{
	int	i;

	i = 0;
	while (str[i] && i < (len - 1))
	{
		res[i] = str[i];
		i++;
	}
	res[i] = 0;
}

char	**ft_split(char const *s, char c)
{
	char	**res;
	char	*str;
	int		str_len;
	int		i;

	if (!s)
		return (NULL);
	res = malloc(sizeof(char *) * (ft_count(s, c) + 1));
	if (!res)
		return (NULL);
	i = 0;
	str = (char *)s;
	str_len = 0;
	while (i < ft_count(s, c))
	{
		ft_len(&str, &str_len, c);
		res[i] = malloc(sizeof(char) * (str_len + 1));
		if (!res[i])
			return (ft_free(res));
		ft_full(res[i], str, str_len + 1);
		i++;
	}
	res[i] = NULL;
	return (res);
}
