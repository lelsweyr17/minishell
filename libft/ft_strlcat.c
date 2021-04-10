/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmarsha <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/31 14:27:19 by cmarsha           #+#    #+#             */
/*   Updated: 2020/11/10 12:36:07 by cmarsha          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t dstsize)
{
	int size;
	int dsize;
	int buf;
	int buff;

	buf = 0;
	buf = ft_strlen(dst);
	buff = buf;
	size = ft_strlen(src);
	if (dstsize < (size_t)buf)
		buff = dstsize;
	if ((dsize = dstsize - buf - 1) < 0)
		dsize = 0;
	while ((dsize--) && (*src))
		dst[buf++] = *src++;
	dst[buf] = '\0';
	return (size + buff);
}
