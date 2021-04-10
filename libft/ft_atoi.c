/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmarsha <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/01 19:44:31 by cmarsha           #+#    #+#             */
/*   Updated: 2020/11/03 19:09:02 by cmarsha          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

static	int	count(const char *str, int i)
{
	int n;

	n = 0;
	while (str[i] >= '0' && str[i] <= '9')
	{
		i++;
		n++;
	}
	if (n <= 19)
		return (0);
	return (1);
}

int			ft_atoi(const char *str)
{
	int				i;
	int				n;
	int				s;
	long long int	r;

	n = 1;
	i = 0;
	r = 0;
	while ((str[i] > 8 && str[i] <= 13) || str[i] == '\r' || str[i] == ' ')
		i++;
	if (str[i] == '+')
		i++;
	else if (str[i] == '-')
	{
		n = -1;
		i++;
	}
	if (str[i] >= '0' && str[i] <= '9')
	{
		if ((s = count(str, i)) == 1)
			return (n == 1 ? -1 : 0);
	}
	while (str[i] >= '0' && str[i] <= '9')
		r = r * 10 + str[i++] - '0';
	return (r * n);
}
