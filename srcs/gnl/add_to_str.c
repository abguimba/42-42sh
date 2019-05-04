/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_to_str.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjose <mjose@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/19 13:51:33 by bsiche            #+#    #+#             */
/*   Updated: 2019/05/04 07:37:51 by mjose            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh42.h"

void		init_str(void)
{
	if (!(g_tracking.str = ft_malloc(sizeof(char) * g_tracking.buffsize)))
	{
		ft_putendl("Failled to allocate memory");
		ft_exit2(EXIT_FAILURE);
	}
	ft_bzero(g_tracking.str, g_tracking.buffsize);
}

void		err_check(int i, int j)
{
	char	*newstr;

	newstr = NULL;
	while ((i + j + 20) > g_tracking.buffsize)
		g_tracking.buffsize *= 2;
	newstr = ft_malloc(sizeof(char) * g_tracking.buffsize);
	ft_bzero(newstr, g_tracking.buffsize);
	newstr = ft_strcpy(newstr, g_tracking.str);
	ft_strdel(&g_tracking.str);
	g_tracking.str = newstr;
}

void		print_and_free(char *str, int i)
{
	ft_free(str);
	if (g_tracking.interactive == 1)
		print_line();
	g_tracking.pos->abs += i;
	if (g_tracking.interactive == 1)
		back_to_pos();
}

void		add_to_str(char *str)
{
	int		i;
	int		a;
	int		len_src;
	int		len_dest;

	if (str != NULL && ft_strlen(str) != 0)
	{
		i = utf_strlen(str);
		a = g_tracking.pos->abs;
		if (!g_tracking.str)
			init_str();
		len_src = ft_strlen(str);
		len_dest = ft_strlen(g_tracking.str);
		a = utf_goto(g_tracking.str, a);
		err_check(len_dest, len_src);
		if (a > (int)ft_strlen(g_tracking.str))
			a = ft_strlen(g_tracking.str);
		ft_memmove(g_tracking.str + a + len_src, g_tracking.str
		+ a, len_dest - a + 1);
		ft_memcpy(g_tracking.str + a, str, len_src);
		print_and_free(str, i);
	}
}
