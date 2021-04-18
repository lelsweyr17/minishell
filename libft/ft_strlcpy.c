/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lelsweyr <lelsweyr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/29 16:06:24 by lelsweyr          #+#    #+#             */
/*   Updated: 2021/04/18 21:54:23 by lelsweyr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcpy(char *dst, const char *src,
								size_t dstsize)
{
	size_t			i;
	unsigned char	*d;
	unsigned char	*s;

	i = 0;
	if (!src)
		return (0);
	s = (unsigned char *)src;
	d = (unsigned char *)dst;
	if (dstsize > 0)
	{
		while (s[i] && i < (dstsize - 1))
		{
			d[i] = s[i];
			i++;
		}
		d[i] = '\0';
	}
	while (s[i])
		i++;
	return (i);
}
