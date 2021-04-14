/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmarsha <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/03 17:40:09 by cmarsha           #+#    #+#             */
/*   Updated: 2021/01/24 14:43:47 by cmarsha          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	unsigned char	*res;
	size_t			l1;
	size_t			l2;

	if (!s1 || !s2)
		return (0);
	l1 = ft_strlen(s1);
	l2 = ft_strlen(s2);
	res = malloc(l1 + l2 + 1);
	if (!res)
		return (0);
	ft_memcpy(res, s1, l1);
	res += l1;
	ft_memcpy(res, s2, l2);
	res -= l1;
	res[l1 + l2] = '\0';
	return (char *)(res);
}

char	**ft_arrjoin(char **s1, char **s2)
{
	char	**res;
	size_t	l1;
	size_t	l2;
	int		i;

	i = -1;
	if (!s1 || !s2)
		return (0);
	l1 = ft_arrlen(s1);
	l2 = ft_arrlen(s2);
	res = malloc(sizeof(char **) * (l1 + l2 + 1));
	if (!res)
		return (0);
	while(++i < l1)
		res[i] = s1[i];
	// ft_memcpy(res, (char *)s1, l1);
	res += l1;
	i = -1;
	while(++i < l2)
		res[i] = s2[i];
	// ft_memcpy(res, (char *)s2, l2);
	res -= l1;
	res[l1 + l2] = 0;
	return (res);
}
