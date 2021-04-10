/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmarsha <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/30 14:50:00 by cmarsha           #+#    #+#             */
/*   Updated: 2020/11/09 19:27:39 by cmarsha          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	const unsigned char *arr;

	arr = s;
	while (n--)
	{
		if (*arr++ == (unsigned char)c)
			return ((void *)(arr - 1));
	}
	return (0);
}
