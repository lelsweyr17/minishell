/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmarsha <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/02 20:59:02 by cmarsha           #+#    #+#             */
/*   Updated: 2021/01/24 14:40:39 by cmarsha          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s1)
{
	size_t			i;
	unsigned char	*a;

	if (!s1)
		return (0);
	i = ft_strlen(s1);
	a = malloc(i + 1);
	if (!a)
		return (0);
	ft_memcpy(a, s1, i);
	a[i] = '\0';
	return ((char *)a);
}
