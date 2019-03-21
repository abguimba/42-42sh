/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rem_from_str.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abguimba <abguimba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/06 04:08:00 by bsiche            #+#    #+#             */
/*   Updated: 2019/03/20 06:11:03 by abguimba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh42.h"

void		rem_from_str(void)
{
	int		a;
	int		b;
	char	*start;
	char	*end;

	b = g_tracking.pos->abs;
	a = b - 1;
	if (g_tracking.str != NULL && b > 0)
	{
		a = utf_goto(g_tracking.str, a);
		b = utf_goto(g_tracking.str, b);
		start = ft_strsub(g_tracking.str, 0, a, 0);
		end = ft_strsub(g_tracking.str, b, ft_strlen(g_tracking.str), 0);
		end = ft_strjoinfree(start, end, 3);
		free(g_tracking.str);
		g_tracking.str = malloc(sizeof(char) * g_tracking.buffsize);
		g_tracking.str = ft_strcpy(g_tracking.str, end);
		free(end);
		print_line();
		g_tracking.pos->abs -= 1;
		back_to_pos();
	}
}

void		rem_from_str_del(void)
{
	int		a;
	int		b;
	char	*start;
	char	*end;

	b = g_tracking.pos->abs + 1;
	a = b - 1;
	if (g_tracking.str != NULL && b > 0)
	{
		a = utf_goto(g_tracking.str, a);
		b = utf_goto(g_tracking.str, b);
		start = ft_strsub(g_tracking.str, 0, a, 0);
		end = ft_strsub(g_tracking.str, b, ft_strlen(g_tracking.str), 0);
		end = ft_strjoinfree(start, end, 3);
		free(g_tracking.str);
		g_tracking.str = malloc(sizeof(char) * g_tracking.buffsize);
		g_tracking.str = ft_strcpy(g_tracking.str, end);
		free(end);
		print_line();
		back_to_pos();
	}
}

void		rem_str(char *str)
{
	int		i;

	i = utf_strlen(str);
	while (i > 0)
	{
		rem_from_str();
		i--;
	}
}
