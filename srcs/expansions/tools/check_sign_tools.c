/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_sign_tools.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjose <mjose@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/12 02:40:58 by mjose             #+#    #+#             */
/*   Updated: 2019/05/03 05:20:52 by mjose            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expansions.h"

char		check_sign(t_expand *expand)
{
	t_expand	*to_run;
	char		sign;

	to_run = expand;
	sign = '\0';
	while (to_run)
	{
		if (!sign)
		{
			sign = is_slash_sign(to_run);
			if (!sign)
				sign = is_two_points_sign(to_run);
			if (!sign)
				sign = is_diferent_sign(to_run);
			if (is_invalid_char(to_run))
			{
				sign = 'E';
				break ;
			}
		}
		to_run = to_run->next;
	}
	return (sign);
}

int			is_invalid_char(t_expand *to_run)
{
	if (to_run && to_run->ltr)
	{
		if ((to_run->ltr == '-'
				|| to_run->ltr == '='
				|| to_run->ltr == '?'
				|| to_run->ltr == '+')
				&& to_run->prev && to_run->prev->ltr != ':')
			return (1);
	}
	return (0);
}

char		is_slash_sign(t_expand *to_run)
{
	if (to_run->ltr == '/')
		return ('/');
	return ('\0');
}

char		is_diferent_sign(t_expand *to_run)
{
	if (to_run->ltr == '#' && to_run->prev && to_run->prev->ltr == '$')
		return ('@');
	else if (to_run->ltr == '#' && to_run->next && to_run->next->ltr != '}'
			&& to_run->prev && to_run->prev->ltr != '{'
			&& to_run->prev->ltr != '#' && to_run->next->ltr != '#')
		return ('#');
	else if (to_run->ltr == '#' && to_run->next && to_run->next->ltr == '#'
			&& to_run->next->next && to_run->next->next->ltr != '}'
			&& to_run->prev && to_run->prev->ltr != '{'
			&& to_run->prev->ltr != '#')
		return ('3');
	else if (to_run->ltr == '%' && to_run->next && to_run->next->ltr != '}'
			&& to_run->prev && to_run->prev->ltr != '{'
			&& to_run->prev->ltr != '%' && to_run->next->ltr != '%')
		return ('%');
	else if (to_run->ltr == '%' && to_run->next && to_run->next->ltr == '%'
			&& to_run->next->next && to_run->next->next->ltr != '}'
			&& to_run->prev && to_run->prev->ltr != '{'
			&& to_run->prev->ltr != '%')
		return ('5');
	else if ((to_run->ltr == '#' && !to_run->next) || (to_run->ltr == '%'
			&& !to_run->next))
		return ('*');
	return ('\0');
}

char		is_two_points_sign(t_expand *to_run)
{
	if (to_run->ltr == ':' && to_run->next)
	{
		if (to_run->next->ltr == '-')
			return ('-');
		else if (to_run->next->ltr == '=')
			return ('=');
		else if (to_run->next->ltr == '?')
			return ('?');
		else if (to_run->next->ltr == '+')
			return ('+');
	}
	return ('\0');
}
