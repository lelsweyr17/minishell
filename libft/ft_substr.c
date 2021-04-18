/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lelsweyr <lelsweyr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/02 12:06:44 by lelsweyr          #+#    #+#             */
/*   Updated: 2021/04/18 21:54:04 by lelsweyr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(const char *s, unsigned int start, size_t len)
{
	size_t	i;
	size_t	j;
	char	*sub;
	int		slen;

	i = 0;
	j = start;
	if (!s)
		return (NULL);
	slen = ft_strlen((char *)s);
	if ((unsigned int)slen <= start)
	{
		sub = (char *)ft_calloc(1, sizeof(char));
		return (sub);
	}
	else
		sub = (char *)ft_calloc((len + 1), sizeof(char));
	if (!sub)
		return (NULL);
	while (s[j] && i < len)
		sub[i++] = s[j++];
	return (sub);
}
