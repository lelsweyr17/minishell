/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strndup.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmarsha <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/12 19:48:24 by cmarsha           #+#    #+#             */
/*   Updated: 2021/04/12 19:48:43 by cmarsha          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strndup(const char *s1, size_t n)
{
	size_t			i;
	unsigned char	*a;

	if (!s1)
		return (0);
	i = ft_strlen(s1);
	if (i < n)
		n = i;
	a = malloc(n + 1);
	if (!a)
		return (0);
	ft_memcpy(a, s1, n);
	a[n] = '\0';
	return ((char *)a);
}
