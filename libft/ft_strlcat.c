/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lelsweyr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/29 17:58:25 by lelsweyr          #+#    #+#             */
/*   Updated: 2020/11/07 15:17:55 by lelsweyr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t		ft_strlcat(char *dst, const char *src, size_t dstsize)
{
	size_t ssize;
	size_t dsize;
	size_t dd;

	if (!dst && !src)
		return (0);
	ssize = ft_strlen((char *)src);
	dsize = ft_strlen((char *)dst);
	dd = dsize;
	if (dstsize <= (size_t)dsize)
		return (ssize + dstsize);
	while (dsize < (dstsize - 1) && *src)
		dst[dsize++] = *src++;
	dst[dsize] = '\0';
	return (ssize + dd);
}
