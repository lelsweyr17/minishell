/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lelsweyr <lelsweyr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/24 14:27:13 by cmarsha           #+#    #+#             */
/*   Updated: 2021/05/06 15:37:32 by lelsweyr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strcpy(char *dst, char *src)
{
	int	i;

	i = -1;
	if (!dst || !src)
		return (0);
	while (src[++i])
		dst[i] = src[i];
	dst[i] = '\0';
	return (dst);
}
