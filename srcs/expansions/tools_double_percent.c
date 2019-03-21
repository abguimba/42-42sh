/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools_double_percent.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjose <mjose@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/20 02:49:07 by mjose             #+#    #+#             */
/*   Updated: 2019/03/20 03:10:19 by mjose            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expansions.h"
#include "sh42.h"

void	ass_str_wend_ast(t_analyzer *to_analy, char **str)
{
	char		*run_varvalue;
	char		*run_wildcard;
	int			i;

	i = 0;
	run_varvalue = to_analy->varvalue;
	run_wildcard = to_analy->wildcard;
	if (to_analy->start_astrsk)
		run_wildcard = run_wildcard + 2;
	run_wildcard[to_analy->wlcd_len] = '\0';
	while (*run_varvalue && !ft_strnstr(run_varvalue, run_wildcard,
		to_analy->wlcd_len))
	{
		run_varvalue++;
		i++;
	}
	run_varvalue = ft_strrev(to_analy->varvalue, 0);
	ft_strdel(str);
	*str = ft_strdup(ft_strrev(run_varvalue + (to_analy->vvlu_len - i), 0));
}

void	ass_str_wstrt_ast(t_analyzer *to_analy, char **str)
{
	char	*run_varvalue;
	char	*run_wildcard;

	run_varvalue = ft_strrev(to_analy->varvalue, 0);
	run_wildcard = ft_strrev(to_analy->wildcard + 1, 0);
	ft_strdel(str);
	if (ft_strnstr(run_varvalue, run_wildcard, to_analy->wlcd_len))
		*str = ft_strdup("");
	else
		*str = ft_strdup(to_analy->varvalue);
}

void	ass_str_wout_ast(t_analyzer *to_analy, char **str)
{
	char	*run_varvalue;
	char	*run_wildcard;

	if (to_analy->varvalue && !to_analy->asterisk)
	{
		run_varvalue = ft_strrev(to_analy->varvalue, 0);
		run_wildcard = ft_strrev(to_analy->wildcard, 0);
		ft_strdel(str);
		if (ft_strnstr(run_varvalue, run_wildcard, to_analy->wlcd_len))
		{
			*str = ft_strdup(run_varvalue + to_analy->wlcd_len);
			*str = ft_strrev(*str, 1);
		}
		else
			*str = ft_strdup(to_analy->varvalue);
	}
}
