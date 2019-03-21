/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   percent_tools.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjose <mjose@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/13 05:33:22 by mjose             #+#    #+#             */
/*   Updated: 2019/03/17 03:06:45 by mjose            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expansions.h"

void	select_last_not_found(char **str, char *value, char *srch, char *found)
{
	int		total;
	int		total_found;
	int		i;
	char	*tmp;

	i = 0;
	total = ft_strlen(value);
	total_found = ft_strlen(srch);
	ft_strdel(str);
	tmp = ft_strnew(total - total_found);
	while ((*value != *found) || (ft_strlen(found) != ft_strlen(value)))
	{
		tmp[i] = *value;
		value++;
		i++;
	}
	*str = tmp;
	if (!**str)
	{
		ft_strdel(str);
		*str = value;
	}
}

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
			to_analy->wildcard) + 1, 0);
	}
	else if (to_analy->varvalue)
	{
		ft_strdel(str);
		*str = ft_strrev(to_analy->varvalue, 1);
	}
	else
	{
		ft_strdel(str);
		*str = ft_strnew(0);
	}
}
