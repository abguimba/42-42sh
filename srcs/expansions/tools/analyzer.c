/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   analyzer.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjose <mjose@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/10 18:01:55 by mjose             #+#    #+#             */
/*   Updated: 2019/04/21 21:23:44 by mjose            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expansions.h"
#include "sh42.h"

void	clean_nlzr_wildcard(t_analyzer *to_analy, int reverse)
{
	char	*tmp;

	if (to_analy->wildcard[0] == '*')
	{
		tmp = ft_strrev(ft_strdup(to_analy->wildcard + 1), 1);
		ft_strdel(&to_analy->wildcard);
		to_analy->wildcard = tmp;
	}
	else
		to_analy->wildcard = ft_strrev(to_analy->wildcard, 1);
	if (to_analy->wildcard[0] == '*')
	{
		tmp = ft_strdup(to_analy->wildcard + 1);
		ft_strdel(&to_analy->wildcard);
		to_analy->wildcard = tmp;
	}
	if (!reverse)
		to_analy->wildcard = ft_strrev(to_analy->wildcard, 1);
}

void	end_analyzer(t_analyzer to_analy)
{
	ft_strdel(&to_analy.varname);
	ft_strdel(&to_analy.varvalue);
	ft_strdel(&to_analy.wildcard);
}

void	init_analyzer(t_analyzer *to_analy, char **str, t_expand *expand)
{
	to_analy->orig_str = *str;
	to_analy->orig_len = ft_strlen(to_analy->orig_str);
	to_analy->varname = get_varname(expand);
	to_analy->vnme_len = ft_strlen(to_analy->varname);
	to_analy->varvalue = ft_strdup(get_env_string(to_analy->varname));
	if (!to_analy->varvalue)
		to_analy->varvalue = ft_strdup(get_set_env_string(to_analy->varname));
	to_analy->vvlu_len = ft_strlen(to_analy->varvalue);
	to_analy->wildcard = get_value(expand, 0);
	to_analy->wlcd_len = ft_strlen(to_analy->wildcard);
	to_analy->start_astrsk = 0;
	to_analy->end_astrsk = 0;
	if (to_analy->wildcard[0]
		&& (to_analy->wildcard[to_analy->wlcd_len - 1] == '*'
			|| to_analy->wildcard[0] == '*'))
	{
		to_analy->asterisk = 1;
		to_analy->wlcd_len--;
		if (to_analy->wildcard[0] == '*')
			to_analy->start_astrsk = 1;
		if (to_analy->wildcard[to_analy->wlcd_len] == '*')
			to_analy->end_astrsk = 1;
	}
	else
		to_analy->asterisk = 0;
}
