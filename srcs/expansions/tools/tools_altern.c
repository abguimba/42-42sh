/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools_altern.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjose <mjose@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/29 03:46:10 by mjose             #+#    #+#             */
/*   Updated: 2019/04/22 03:55:00 by mjose            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expansions.h"
#include "sh42.h"

void	reassign_str_altern(char **str, t_analyzer *to_analy)
{
	if (to_analy->varvalue)
	{
		ft_strdel(str);
		*str = ft_strdup(to_analy->varvalue);
	}
	else
	{
		ft_strdel(str);
		*str = ft_strdup("");
	}
}
