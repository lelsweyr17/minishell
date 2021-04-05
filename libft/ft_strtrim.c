/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lelsweyr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/02 13:56:00 by lelsweyr          #+#    #+#             */
/*   Updated: 2020/11/04 14:07:24 by lelsweyr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int		found(char s, char const *set)
{
	int			i;

	i = 0;
	while (set[i])
	{
		if (set[i] == s)
			return (1);
		i++;
	}
	return (0);
}

char			*ft_strtrim(char const *s1, char const *set)
{
	char		*res;
	int			st;
	int			fin;
	int			i;

	st = 0;
	i = 0;
	if (!s1 || !set)
		return (NULL);
	fin = ft_strlen((char *)s1) - 1;
	while (s1[st] && found(s1[st], set) == 1)
		st++;
	while (fin > st && found(s1[fin], set) == 1)
		fin--;
	res = (char *)malloc((fin - st + 2) * sizeof(char));
	if (!res)
		return (NULL);
	while (st <= fin)
		res[i++] = s1[st++];
	res[i] = '\0';
	return (res);
}
