/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lelsweyr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/30 14:38:15 by lelsweyr          #+#    #+#             */
/*   Updated: 2020/11/06 19:25:03 by lelsweyr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static long long	res(char *str, int i)
{
	long long		n;
	int				count;

	n = 0;
	count = 1;
	while (str[i] >= '0' && str[i] <= '9' && str[i] != '\0')
	{
		n = (n * count) + (str[i] - '0');
		count = 10;
		i++;
	}
	return (n);
}

static int			count(char *str, int i)
{
	int				n;

	n = 0;
	while (str[i + n] >= '0' && str[i + n] <= '9' && str[i + n] > 32)
		n++;
	if ((str[i] < '0' || str[i] > '9') && (str[i] != '\0'
		|| str[i] != '+' || str[i] != '-' || str[i] == '\e'))
		return (0);
	if (n > 19)
		return (-1);
	return (1);
}

int					ft_atoi(char *str)
{
	int				i;
	int				z;
	long long		re;

	i = 0;
	re = 0;
	z = 0;
	while ((str[i] >= 8 && str[i] <= 13) || str[i] == 32)
		i++;
	z = i;
	if (str[i] == '-' || str[i] == '+')
		i++;
	if (count(str, i) == 0)
		return (0);
	if (count(str, i) == -1 && str[z] == '-')
		return (0);
	else if (count(str, i) == -1)
		return (-1);
	re = res(str, i);
	if (str[z] == '-')
		re = -re;
	return (re);
}
