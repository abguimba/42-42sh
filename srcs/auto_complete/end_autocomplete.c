/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   end_autocomplete.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abguimba <abguimba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/06 00:29:34 by bsiche            #+#    #+#             */
/*   Updated: 2019/03/20 06:11:03 by abguimba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh42.h"

void	add_choice(int i)
{
	char	*add;

	add = g_tracking.aut->to_add;
	if (i == 1)
	{
		if (g_tracking.aut->type == 1)
			escape_path();
		if (g_tracking.aut->type == 2)
			g_tracking.aut->to_add = ft_strjoinfree(add, "} ", 1);
		if ((g_tracking.aut->type != 2) && (g_tracking.aut->type != 1))
			g_tracking.aut->to_add = ft_strjoinfree(add, " ", 1);
		add_to_str(g_tracking.aut->to_add);
		g_tracking.aut->to_add = NULL;
	}
	else
	{
		if (g_tracking.aut->word)
		{
			add_to_str(g_tracking.aut->word);
			g_tracking.aut->word = NULL;
		}
	}
}

int		end_autocomplete(int i)
{
	print_line();
	back_to_pos();
	if (g_tracking.aut)
		add_choice(i);
	tputs(tgetstr("ve", NULL), 1, yan_putchar);
	return (0);
}
