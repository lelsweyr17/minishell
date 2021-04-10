/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmarsha <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/30 12:37:04 by cmarsha           #+#    #+#             */
/*   Updated: 2020/11/02 22:30:23 by cmarsha          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t n)
{
	unsigned char		*d;
	const unsigned char *s;

	d = dst;
	s = src;
	if ((!dst) && (!src))
		return (0);
	if (s < d)
		while (n-- > 0)
		{
			d[n] = s[n];
		}
	else
		while (n--)
			*d++ = *s++;
	return (dst);
}
