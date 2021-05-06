/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lelsweyr <lelsweyr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/02 16:44:06 by cmarsha           #+#    #+#             */
/*   Updated: 2021/05/06 15:43:11 by lelsweyr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	while (n)
	{
		if ((*s1 == *s2) && (*s1) && (*s2) && (n > 0) \
			&& (*s1 != '\0') && (*s2 != '\0'))
		{
			n--;
			s1 += 1;
			s2 += 1;
		}
		else
			return (*(unsigned char *)s1 - *(unsigned char *)s2);
	}
	return (0);
}
