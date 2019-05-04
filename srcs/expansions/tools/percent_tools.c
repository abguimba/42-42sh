/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   percent_tools.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjose <mjose@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/13 05:33:22 by mjose             #+#    #+#             */
/*   Updated: 2019/04/08 10:35:34 by mjose            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expansions.h"

void	select_not_found(char **str, char *value_var, char *to_srch)
{
	int		total_found;
	char	*tmp;
	int		i;

	total_found = ft_strlen(to_srch);
	i = 0;
	ft_strdel(str);
	tmp = value_var;
	while (total_found != i++)
		tmp++;
	*str = ft_strrev(tmp, 0);
}

void	str_uniq_percent_chgr(t_analyzer *to_analy, char **str)
{
	if (to_analy->varvalue && ft_strnstr(to_analy->varvalue, to_analy->wildcard,
			to_analy->wlcd_len))
		select_not_found(str, to_analy->varvalue, to_analy->wildcard);
	else if (to_analy->varvalue && ft_strstr(to_analy->varvalue,
			to_analy->wildcard) && to_analy->end_astrsk)
	{
		ft_strdel(str);
		*str = ft_strrev(ft_strstr(to_analy->varvalue,
			to_analy->wildcard) + to_analy->wlcd_len, 0);
	}
	else if (to_analy->varvalue)
	{
		ft_strdel(str);
		*str = ft_strrev(to_analy->varvalue, 0);
	}
	else
	{
		ft_strdel(str);
		*str = ft_strnew(0);
	}
}
