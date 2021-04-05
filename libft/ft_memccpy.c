/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memccpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lelsweyr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/28 16:56:04 by lelsweyr          #+#    #+#             */
/*   Updated: 2020/11/02 10:51:12 by lelsweyr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void				*ft_memccpy(void *dst, const void *src,
								int c, size_t n)
{
	unsigned char	*a;
	unsigned char	*b;
	unsigned char	k;

	a = (unsigned char *)src;
	b = (unsigned char *)dst;
	k = (unsigned char)c;
	if (!a && !b)
		return (NULL);
	while (n--)
	{
		*b++ = *a++;
		if (*(b - 1) == k)
			return (b);
	}
	return (NULL);
}
