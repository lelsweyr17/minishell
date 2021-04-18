/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lelsweyr <lelsweyr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/30 11:44:48 by lelsweyr          #+#    #+#             */
/*   Updated: 2021/04/18 21:54:15 by lelsweyr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	unsigned char	*d1;
	unsigned char	*d2;

	d1 = (unsigned char *)s1;
	d2 = (unsigned char *)s2;
	while ((*d1 != '\0' || *d2 != '\0') && n--)
	{
		if (*d1 < *d2)
			return (-1);
		else if (*d1 > *d2)
			return (1);
		d1++;
		d2++;
	}
	return (0);
}
