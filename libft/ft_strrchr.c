/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lelsweyr <lelsweyr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/30 10:48:03 by lelsweyr          #+#    #+#             */
/*   Updated: 2021/04/12 18:42:11 by lelsweyr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	char			*a;
	unsigned int	count;
	unsigned char	k;

	a = (char *)s;
	k = (unsigned char)c;
	count = ft_strlen(a) + 1;
	a = a + count - 1;
	if (s == '\0')
		return (0);
	while (count > 0)
	{
		if (*a == k)
			return (a);
		a--;
		count--;
	}
	return (NULL);
}
