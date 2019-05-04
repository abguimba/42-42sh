/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools_double_hash.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjose <mjose@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/19 22:52:02 by mjose             #+#    #+#             */
/*   Updated: 2019/04/22 03:55:12 by mjose            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expansions.h"
#include "sh42.h"

void	rmv_str(char **str)
{
	ft_strdel(str);
	*str = ft_strdup("");
}

void	asgnvrvluastrk(t_analyzer *nly, char **rvrvlu, char **rwlcd, char **str)
{
	char	*run_varvalue;
	char	*run_wildcard;
	char	*cop_varvalue;
	int		i;

	i = 0;
	run_varvalue = ft_strrev(*rvrvlu, 0);
	cop_varvalue = run_varvalue;
	run_wildcard = ft_strrev(*rwlcd, 0);
	if (!ft_strnstr(run_varvalue, run_wildcard, nly->wlcd_len))
		while (!ft_strnstr(cop_varvalue, run_wildcard, nly->wlcd_len))
		{
			cop_varvalue++;
			i++;
			if (!cop_varvalue || i > nly->vvlu_len)
				break ;
		}
	ft_strdel(str);
	if (i > nly->vvlu_len)
		*str = ft_strdup(nly->varvalue);
	else
		*str = ft_strdup(nly->varvalue + (nly->vvlu_len - i));
	ft_strdel(&run_wildcard);
	ft_strdel(&run_varvalue);
}

void	asign_vrvlufnd(t_analyzer *nly, char **rvrvlu, char **rwlcd, char **str)
{
	ft_strdel(str);
	if (ft_strnstr(*rvrvlu, *rwlcd, nly->wlcd_len))
		*str = ft_strdup(*rvrvlu + nly->wlcd_len);
	else
		*str = ft_strdup(nly->varvalue);
}
