/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   values.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjose <mjose@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/14 06:10:51 by mjose             #+#    #+#             */
/*   Updated: 2019/03/21 07:02:02 by mjose            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expansions.h"

char	*get_value_asterisk(t_expand *expand)
{
	int			i;
	char		*value;
	t_expand	*start;
	t_expand	*to_run;

	i = 0;
	to_run = expand->next;
	while (to_run->ltr != ':' && to_run->ltr != '%')
		to_run = to_run->next;
	if (to_run->ltr == '%')
	{
		if (to_run->next->ltr == '%')
			to_run = to_run->next;
		to_run = to_run->prev;
	}
	start = to_run->next->next;
	while (start->ltr != '*')
	{
		start = start->next;
		i++;
	}
	value = ft_strnew(i);
	return (value_asterisk(value, to_run->next->next));
}

char	*get_asterisk_value(t_expand *expand)
{
	int			i;
	char		*val;
	t_expand	*start;
	t_expand	*to_run;

	i = 0;
	to_run = expand->next;
	while (to_run->ltr != ':' && to_run->ltr != '#')
		to_run = to_run->next;
	if (to_run->ltr == '#')
	{
		if (to_run->next->ltr == '#')
			to_run = to_run->next;
		if (to_run->next->ltr == '*')
			to_run = to_run->next;
		to_run = to_run->prev;
	}
	start = to_run->next->next;
	while (start && start->ltr != '*'/*->ltr != '}'*/)
	{
		start = start->next;
		i++;
	}
	val = ft_strnew(i);
	return (value(val, to_run->next->next));
}

char	*get_value(t_expand *expand)
{
	int			i;
	char		*val;
	t_expand	*start;
	t_expand	*to_run;

	i = 0;
	to_run = expand->next;
	while (to_run && to_run->ltr != ':' && to_run->ltr != '#'
			&& to_run->ltr != '%' && to_run->ltr != '/')
		to_run = to_run->next;
	if (!to_run && to_run->prev->ltr == '$')
		return(NULL);
	if (to_run->ltr == '#' || to_run->ltr == '%' || to_run->ltr == '/')
	{
		if (to_run->next && to_run->prev)
			if (to_run->next->ltr == '#' || to_run->next->ltr == '%')
				to_run = to_run->next;
		to_run = to_run->prev;
	}
	if (!to_run->next)
		return (NULL);
	if (!to_run->next->next)
		return (ft_strdup(" "));
	start = to_run->next->next;
	while (start && start->ltr != '}')
	{
		if (start/* && start->next->ltr*/)
		{
			start = start->next;
			i++;
		}
		else
			break ;
	}
	if (!i)
		return (NULL);
	val = ft_strnew(i + 1);
	return (value(val, to_run->next->next));
}

char	*get_varname(t_expand *expand)
{
	int			i;
	char		*var;
	t_expand	*to_run;

	i = 0;
//	to_run = expand->next->next;
	to_run = expand->next;
	if (to_run->ltr == '#' || to_run->ltr == '%')
		to_run = to_run->next;
	while (to_run && to_run->ltr != ':' && to_run->ltr != '}'
			&& to_run->ltr != '/' && (to_run->ltr != '#' || to_run->ltr != '%'))
	{
		to_run = to_run->next;
		i++;
	}
	var = ft_strnew(i + 1);
	to_run = expand->next;
	return (varname(var, to_run));
}
