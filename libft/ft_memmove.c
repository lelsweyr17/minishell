/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lelsweyr <lelsweyr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/30 12:37:04 by cmarsha           #+#    #+#             */
/*   Updated: 2021/05/06 15:41:43 by lelsweyr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t n)
{
	unsigned char		*d;
	const unsigned char	*s;

	d = dst;
	s = src;
	if ((!dst) && (!src))
		return (0);
	if (s < d)
	{	
		while (n-- > 0)
		{
			d[n] = s[n];
		}
	}
	else
		while (n--)
			*d++ = *s++;
	return (dst);
}
