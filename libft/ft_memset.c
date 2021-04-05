/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lelsweyr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/28 15:32:55 by lelsweyr          #+#    #+#             */
/*   Updated: 2020/11/01 13:04:24 by lelsweyr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void				*ft_memset(void *b, int a, size_t len)
{
	size_t			i;
	unsigned char	*k;
	unsigned char	m;

	i = 0;
	k = (unsigned char *)b;
	m = (unsigned char)a;
	while (i < len)
	{
		k[i] = m;
		i++;
	}
	return (b);
}
