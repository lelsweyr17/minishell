/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lelsweyr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/30 10:31:44 by lelsweyr          #+#    #+#             */
/*   Updated: 2020/11/01 13:00:51 by lelsweyr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char				*ft_strchr(const char *s, int c)
{
	int				i;
	unsigned char	sym;
	char			*a;

	i = 0;
	a = (char *)s;
	sym = (unsigned char)c;
	if (sym == '\0')
	{
		while (a[i] != '\0')
			i++;
		return (&a[i]);
	}
	while (a[i] != '\0')
	{
		if (a[i] == sym)
			return (&a[i]);
		else
			i++;
	}
	return (NULL);
}
