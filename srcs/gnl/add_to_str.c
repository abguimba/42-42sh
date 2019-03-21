/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_to_str.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abguimba <abguimba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/19 13:51:33 by bsiche            #+#    #+#             */
/*   Updated: 2019/03/20 03:10:22 by bsiche           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/sh42.h"

void		err_check(int i, int j)
{
	char	*newstr;

	newstr = NULL;
	while ((i + j + 7) > g_tracking.buffsize)
	{
		g_tracking.buffsize *= 2;
		newstr = malloc(sizeof(char) * g_tracking.buffsize);
		newstr = ft_strcpy(newstr, g_tracking.str);
		free(g_tracking.str);
		g_tracking.str = newstr;
	}
}

void		print_and_free(char *str, int i)
{
	free(str);
	if (g_tracking.interactive == 1)
		print_line();
	g_tracking.pos->abs += i;
	back_to_pos();
}

void		add_to_str(char *str)
{
	int		i;
	int		a;
	int		len_src;
	int		len_dest;

	if (str != NULL)
	{
		i = utf_strlen(str);
		a = g_tracking.pos->abs;
		if (!g_tracking.str)
			g_tracking.str = ft_strcpy(g_tracking.str, str);
		else
		{
			len_src = ft_strlen(str);
			len_dest = ft_strlen(g_tracking.str);
			a = utf_goto(g_tracking.str, a);
			err_check(len_dest, len_src);
			if (a > utf_strlen(g_tracking.str))
				a = ft_strlen(g_tracking.str);
			ft_memmove(g_tracking.str + a + len_src, g_tracking.str
			+ a, len_dest - a + 1);
			ft_memcpy(g_tracking.str + a, str, len_src);
		}
		print_and_free(str, i);
	}
}
