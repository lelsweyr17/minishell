/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lelsweyr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/02 13:23:52 by lelsweyr          #+#    #+#             */
/*   Updated: 2020/11/02 13:55:51 by lelsweyr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char		*ft_strjoin(char const *s1, char const *s2)
{
	int		i;
	int		j;
	char	*res;
	int		size1;
	int		size2;

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
