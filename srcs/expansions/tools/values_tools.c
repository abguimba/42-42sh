/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   values_tools.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjose <mjose@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/14 06:23:41 by mjose             #+#    #+#             */
/*   Updated: 2019/05/01 07:09:19 by mjose            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expansions.h"

char	*value(char *val, t_expand *start)
{
	int		i;

	i = 0;
	while (start && start->ltr)
	{
		val[i++] = start->ltr;
		start = start->next;
	}
	if (!i)
		return (NULL);
	return (val);
}

char	*varname(char *var, t_expand *to_run)
{
	int		i;

	i = 0;
	if (to_run->ltr == '#' && to_run->ltr != '%')
		to_run = to_run->next;
	while (to_run && to_run->ltr != ':' && to_run->ltr != '}'
			&& to_run->ltr != '#' && to_run->ltr != '%' && to_run->ltr != '/')
	{
		var[i++] = to_run->ltr;
		to_run = to_run->next;
	}
	return (var);
}
