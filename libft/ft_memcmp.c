/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lelsweyr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/28 18:17:24 by lelsweyr          #+#    #+#             */
/*   Updated: 2020/10/31 13:25:14 by lelsweyr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_memcmp(const void *s1, const void *s2, size_t n)
{
	unsigned char *src;
	unsigned char *dest;

	src = (unsigned char *)s1;
	dest = (unsigned char *)s2;
	while (n--)
	{
		if (*src != *dest)
			return (*src - *dest);
		src++;
		dest++;
	}
	return (0);
}
