/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmarsha <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/24 14:27:13 by cmarsha           #+#    #+#             */
/*   Updated: 2021/01/24 14:33:22 by cmarsha          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strcpy(char *dst, char *src)
{
	int i;

	i = -1;
	if (!dst || !src)
		return (0);
	while (src[++i])
		dst[i] = src[i];
	dst[i] = '\0';
	return (dst);
}
