/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_arrjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmarsha <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/15 12:38:05 by cmarsha           #+#    #+#             */
/*   Updated: 2021/04/15 12:38:27 by cmarsha          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	**ft_arrjoin(char **s1, char **s2)
{
	char	**res;
	size_t	l1;
	size_t	l2;
	size_t	i;

	i = -1;
	if (!s1 || !s2)
		return (0);
	l1 = ft_arrlen(s1);
	l2 = ft_arrlen(s2);
	res = malloc(sizeof(char **) * (l1 + l2 + 1));
	if (!res)
		return (0);
	while (++i < l1)
		res[i] = s1[i];
	res += l1;
	i = -1;
	while (++i < l2)
		res[i] = s2[i];
	res -= l1;
	res[l1 + l2] = 0;
	return (res);
}
