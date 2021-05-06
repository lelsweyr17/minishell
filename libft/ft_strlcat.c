/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lelsweyr <lelsweyr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/31 14:27:19 by cmarsha           #+#    #+#             */
/*   Updated: 2021/05/06 15:42:36 by lelsweyr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t dstsize)
{
	int	size;
	int	dsize;
	int	buf;
	int	buff;

	buf = 0;
	buf = ft_strlen(dst);
	buff = buf;
	size = ft_strlen(src);
	if (dstsize < (size_t)buf)
		buff = dstsize;
	dsize = dstsize - buf - 1;
	if (dsize < 0)
		dsize = 0;
	while ((dsize--) && (*src))
		dst[buf++] = *src++;
	dst[buf] = '\0';
	return (size + buff);
}
