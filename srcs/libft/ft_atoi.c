/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjose <mjose@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/01 17:42:16 by bsiche            #+#    #+#             */
/*   Updated: 2019/04/11 23:07:46 by mjose            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int			ft_atoi(const char *nptr)
{
	size_t	i;
	size_t	number;
	size_t	n;

	i = 0;
	n = 1;
	number = 0;
	while (nptr[i] == ' ' || nptr[i] == '\v' || nptr[i] == '\n'
		|| nptr[i] == '\t' || nptr[i] == '\r' || nptr[i] == '\f')
		i++;
	if (nptr[i] == '-' || nptr[i] == '+')
	{
		if (nptr[i] == '-')
			n = -1;
		i++;
	}
	while (nptr[i] >= '0' && nptr[i] <= '9')
	{
		number = number * 10 + nptr[i] - '0';
		i++;
	}
	return (n * number);
}

long		atoi_check_rtn(long flag, size_t n, size_t number)
{
	if (flag == 0)
		return (2147483648);
	return (n * number);
}

int			skip_space(int i, char *nptr)
{
	while (nptr[i] == ' ' || nptr[i] == '\v' || nptr[i] == '\n'
	|| nptr[i] == '\t' || nptr[i] == '\r' || nptr[i] == '\f')
		i++;
	return (i);
}

long		ft_atoi_check(char *nptr)
{
	size_t	i;
	size_t	number;
	size_t	n;
	long	flag;

	i = 0;
	n = 1;
	number = 0;
	flag = 0;
	i = skip_space(i, nptr);
	if (nptr[i] == '-' || nptr[i] == '+')
	{
		if (nptr[i] == '-')
			n = -1;
		i++;
	}
	while (nptr[i] >= '0' && nptr[i] <= '9')
	{
		flag = 1;
		number = number * 10 + nptr[i] - '0';
		i++;
	}
	return (atoi_check_rtn(flag, n, number));
}
