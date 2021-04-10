/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmarsha <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/30 20:10:05 by cmarsha           #+#    #+#             */
/*   Updated: 2020/11/03 16:33:47 by cmarsha          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize)
{
	size_t size;

	if (!src)
		return (0);
	size = ft_strlen(src);
	if (dstsize > 0)
	{
		dstsize--;
		while (*src && dstsize--)
			*dst++ = *src++;
		*dst = '\0';
	}
	return (size);
}
