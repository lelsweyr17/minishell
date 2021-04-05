/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lelsweyr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/30 11:09:06 by lelsweyr          #+#    #+#             */
/*   Updated: 2020/11/01 13:49:44 by lelsweyr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char		*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	size_t	i;
	size_t	j;
	char	*a;

	i = 0;
	j = 0;
	a = (char *)haystack;
	if (needle[j] == '\0')
		return (a);
	while (a[i] != '\0' && len != 0)
	{
		if (needle[j] == a[i])
		{
			while (needle[j] != '\0' && needle[j] == a[i + j] && (i + j) < len)
				j++;
			if (needle[j] == '\0')
				return (&a[i]);
			j = 0;
		}
		i++;
	}
	return (NULL);
}
