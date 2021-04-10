/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmarsha <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/31 20:27:54 by cmarsha           #+#    #+#             */
/*   Updated: 2020/11/02 20:56:47 by cmarsha          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	char	*hst;
	size_t	h;
	size_t	n;

	h = 0;
	n = 0;
	hst = (char *)haystack;
	if (!*needle)
		return (hst);
	while ((hst[h] != '\0') && (len != 0))
	{
		if (hst[h] == needle[n])
		{
			while ((hst[h + n] != '\0') && (hst[h + n] == needle[n]) &&
					(len > (h + n)))
				n++;
			if (needle[n] == '\0')
				return (&hst[h]);
			n = 0;
		}
		h++;
	}
	return (0);
}
