/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   auto_complete_loop.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abguimba <abguimba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/18 20:45:18 by bsiche            #+#    #+#             */
/*   Updated: 2019/03/20 03:02:17 by bsiche           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh42.h"

int		read_loop(void)
{
	long c;

	c = 0;
	if (lstcontainer_size(g_tracking.aut->comp_list) == 1)
		return (end_autocomplete(1));
	read(STDERR_FILENO, &c, 8);
	if (c == 4479771)
		return (-1);
	if (c == 4414235 || c == K_TAB)
		return (1);
	if (c == 4348699)
		return (2);
	if (c == 4283163)
		return (-2);
	if (c == 2117425947)
		return (-3);
	if (c == 2117491483)
		return (3);
	if (c == K_RTN || c == K_SPC)
		return (end_autocomplete(1));
	else
		return (end_autocomplete(0));
}

int		get_new(t_list *buf)
{
	t_ls		*tmp;

	if (buf)
	{
		print_line();
		back_to_pos();
		tmp = buf->content;
		if (g_tracking.aut->to_add)
		{
			free(g_tracking.aut->to_add);
			g_tracking.aut->to_add = NULL;
		}
		g_tracking.aut->to_add = ft_strdup(tmp->name);
		if (g_tracking.aut->type != 2)
		{
			if (tmp->strpermission[0] == 'd' || tmp->strpermission[0] == 'l')
				g_tracking.aut->type = 1;
			else
				g_tracking.aut->type = 0;
		}
		return (print_menu());
	}
	return (0);
}

void	actual_loop(t_lstcontainer *list)
{
	t_list			*buf;
	int				i;

	g_tracking.aut->page_lst = build_page_lst(list);
	buf = g_tracking.aut->page_lst->firstelement;
	if (!buf)
		exit(0);
	get_new(buf);
	i = g_tracking.aut->line_up;
	while ((i = read_loop()) != 0 && buf != NULL)
	{
		if (i == 3 || i == -3)
		{
			if (g_tracking.aut->page_nbr > 0)
			{
				change_page(i, list);
				buf = g_tracking.aut->page_lst->firstelement;
			}
		}
		else
			buf = move_arround(buf, i);
		get_new(buf);
	}
}

void	back_up_err(char *err)
{
	int		y;
	int		ab;

	ab = utf_strlen(g_tracking.str);
	ab += g_tracking.pos->prompt;
	ab += utf_strlen(err);
	y = ab / g_tracking.terminfo->sizex;
	y = y - (g_tracking.pos->y);
	while (y != 0)
	{
		y--;
		tputs(tgetstr("up ", NULL), 1, yan_putchar);
	}
}

void	completion_loop(t_lstcontainer *list)
{
	char	*err;

	err = NULL;
	if (g_tracking.aut->err == 0)
	{
		tputs(tgetstr("vi", NULL), 1, yan_putchar);
		line_per_page();
		actual_loop(list);
		tputs(tgetstr("ve", NULL), 1, yan_putchar);
	}
	if (g_tracking.aut->err == 2)
	{
		err = ft_strdup("Term size too small");
		tputs(tgetstr("do ", NULL), 1, yan_putchar);
		ft_putendl_fd(err, 2);
		back_up_err(err);
	}
}
