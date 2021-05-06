/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lelsweyr <lelsweyr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/03 16:34:58 by cmarsha           #+#    #+#             */
/*   Updated: 2021/05/06 18:07:49 by lelsweyr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

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
	int		count;
	int		i;

	if (!s)
		return (NULL);
	count = ft_count(s, c);
	res = malloc(sizeof(char *) * (count + 1));
	if (!res)
		return (NULL);
	i = -1;
	str = (char *)s;
	str_len = 0;
	while (++i < count)
	{
		ft_len(&str, &str_len, c);
		res[i] = malloc(sizeof(char) * (str_len + 1));
		if (!res)
			return (ft_free(res));
		ft_full(res[i], str, str_len + 1);
	}
	res[i] = NULL;
	return (res);
}
