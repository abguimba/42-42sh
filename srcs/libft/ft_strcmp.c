/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsiche <bsiche@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/01 17:28:08 by bsiche            #+#    #+#             */
/*   Updated: 2018/08/30 21:56:33 by bsiche           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_strcmp(const char *s1, const char *s2)
{
	if (ft_strlen(s1) == 0 || ft_strlen(s2) == 0)
		return (-256);
	return (ft_memcmp(s1, s2, ft_strlen(s1) + 1));
}
