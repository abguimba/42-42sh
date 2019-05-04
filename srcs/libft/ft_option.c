/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_option.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjose <mjose@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/21 04:41:06 by bsiche            #+#    #+#             */
/*   Updated: 2019/04/22 03:59:07 by mjose            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_cleanoption(char *bits, int i, int j, int k)
{
	char	*tmp;
	int		flag;

	tmp = ft_strnew(ft_strlen(bits));
	while (bits[i])
	{
		j = i + 1;
		flag = 0;
		while (bits[j])
		{
			if (bits[i] == bits[j])
				flag++;
			j++;
		}
		if (flag == 0)
		{
			tmp[k] = bits[i];
			k++;
		}
		i++;
	}
	tmp[k] = '\0';
	tmp = clean1(tmp, 0, 0);
	ft_free(bits);
	return (tmp);
}

char	*ft_whatoption(char *str)
{
	int		i;
	int		j;
	char	*bits;

	bits = ft_strnew(ft_strlen(str));
	if (str[0] != '-')
		return (NULL);
	i = 1;
	j = 0;
	while (str[i])
	{
		if (str[i] == 'a' || str[i] == 'R' || str[i] == 'l' || str[i] == 't'
			|| str[i] == 'S' || str[i] == 'r' || str[i] == 'u' || str[i] == 'f'
			|| str[i] == 'd' || str[i] == '1' || str[i] == 'G' || str[i] == '@')
		{
			bits[j] = str[i];
			j++;
		}
		else
			ft_usage(str[i]);
		i++;
	}
	str = ft_cleanoption(bits, 0, 0, 0);
	return (str);
}

char	*ft_option(char **argv)
{
	char	*buf;
	int		i;

	i = 1;
	while (argv[i][0] == '-' && ft_strlen(argv[i]) != 1)
	{
		if ((ft_strcmp(argv[i], "--")) == 0)
			return (str);
		buf = ft_whatoption(argv[i]);
		str = ft_strjoinfree(*str, buf, 3);
		if (argv[i + 1] != NULL)
			i++;
	}
	return (str);
}
