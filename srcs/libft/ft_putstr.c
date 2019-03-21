/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putstr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsiche <bsiche@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/01 20:58:35 by bsiche            #+#    #+#             */
/*   Updated: 2019/03/17 01:31:42 by bsiche           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putstr(char const *s)
{
	int	i;

	if (*s)
	{
		i = ft_strlen(s);
		write(1, s, i);
	}
}

void	ft_putstr_nocar(char const *s)
{
	char	*new;
	int		i;
	int		a;

	new = ft_strnew(ft_strlen(s));
	i = 0;
	a = 0;
	while (s[i] != '\0')
	{
		if (s[i] != '\r')
		{
			new[a] = s[i];
			a++;
		}
		i++;
	}
	ft_putstr_fd(new, 0);
	free(new);
}
