/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmarsha <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/03 16:34:58 by cmarsha           #+#    #+#             */
/*   Updated: 2020/11/10 16:56:54 by cmarsha          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static	void	ft_free(char **split, int i)
{
	while (i >= 0)
		free(split[i--]);
	free(split);
}

static	int		ft_words(char *str, int c)
{
	int i;
	int j;

	i = 0;
	j = 0;
	while (str[i] != '\0')
	{
		while (str[i] == c)
			i++;
		if ((str[i] != c) && (str[i] != '\0'))
			j++;
		while ((str[i] != c) && (str[i] != '\0'))
			i++;
	}
	return (j);
}

static	int		ft_shift(char *str, int c)
{
	int i;

	i = 0;
	while ((*str == c) && (*str != '\0'))
	{
		str++;
		i++;
	}
	if (*str != c)
		return (i);
	return (0);
}

static	char	*next_word(char *str, int j, int bshift)
{
	char	*dest;

	if (!(dest = (char *)malloc(sizeof(char) * (j + 1))))
		return (0);
	while (j--)
		*dest++ = *str++;
	*dest = '\0';
	dest -= bshift;
	return (dest);
}

char			**ft_split(char const *s, char c)
{
	int		i;
	int		words;
	char	**split;
	int		wordnr;

	wordnr = 0;
	if (!s)
		return (0);
	while ((*s == c) && (c != '\0'))
		s++;
	words = ft_words((char *)s, c);
	if (!(split = (char **)malloc(sizeof(char *) * (words + 1))))
		return (0);
	while (words--)
	{
		i = 0;
		s += ft_shift((char *)s, c);
		while ((s[i] != c) && (s[i] != '\0'))
			i++;
		if (!(split[wordnr++] = next_word((char *)s, i, i)))
			ft_free(split, wordnr - 1);
		s += i;
	}
	split[wordnr] = 0;
	return (split);
}
