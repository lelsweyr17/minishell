/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmarsha <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/30 18:40:21 by cmarsha           #+#    #+#             */
/*   Updated: 2020/10/31 14:05:26 by cmarsha          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	const unsigned char *sr1;
	const unsigned char *sr2;

	sr1 = s1;
	sr2 = s2;
	while (n--)
		if (*sr1++ != *sr2++)
			return (*--sr1 - *--sr2);
	return (0);
}
