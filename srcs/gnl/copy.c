/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   copy.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsiche <bsiche@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/10 19:41:54 by bsiche            #+#    #+#             */
/*   Updated: 2019/05/04 03:03:34 by bsiche           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh42.h"

int		ft_mini_exec_key(char *str)
{
	if (ft_strcmp(str, K_LEFT) == 0)
		move_left();
	if (ft_strcmp(str, K_RIGHT) == 0)
		move_right();
	if (ft_strcmp(str, K_WRIGHT) == 0)
		next_word();
	if (ft_strcmp(str, K_WLEFT) == 0)
		prev_word();
	if (ft_strcmp(str, K_LUP) == 0)
		move_up();
	if (ft_strcmp(str, K_LDOWN) == 0)
		move_down();
	if (ft_strcmp(str, K_FN1) == 0)
		return (7);
	if (ft_strcmp(str, K_FN2) == 0)
		return (8);
	return (6);
}

int		mini_is_cmd(char *str)
{
	unsigned long	i;
	t_list			*tmp;
	int				flag;

	i = ft_strlen(str);
	tmp = g_tracking.key_list->firstelement;
	flag = 0;
	while (tmp)
	{
		if (ft_strncmp(str, tmp->content, i) == 0)
			flag++;
		if (ft_strlen(tmp->content) == i
				&& ft_strncmp(str, tmp->content, i) == 0)
			return (ft_mini_exec_key(str));
		tmp = tmp->next;
	}
	if (flag == 0)
		return (6);
	return (0);
}

int		mini_read(int i)
{
	char	c;
	char	*str;

	str = ft_strnew(2);
	read(STDERR_FILENO, &c, 1);
	str = ft_strjoinchar(str, c, 1);
	if (c < 32)
	{
		while (i == 0)
		{
			read(STDERR_FILENO, &c, 1);
			str = ft_strjoinchar(str, c, 1);
			i = mini_is_cmd(str);
			if (i == 6)
				break ;
			if (i > 6)
			{
				ft_free(str);
				return (i);
			}
		}
	}
	ft_free(str);
	return (0);
}

void	ft_actual_cpy(void)
{
	int		start;
	int		end;
	int		len;

	start = g_tracking.cpaste->b1;
	end = g_tracking.cpaste->b2 + 1;
	if (end < start)
	{
		start = g_tracking.cpaste->b2;
		end = g_tracking.cpaste->b1;
	}
	start = utf_goto(g_tracking.str, start);
	end = utf_goto(g_tracking.str, end);
	len = end - start;
	if (g_tracking.cpaste->line)
		ft_strdel(&g_tracking.cpaste->line);
	g_tracking.cpaste->line = ft_strsub(g_tracking.str, start, len, 0);
}

void	begin_cpy(void)
{
	int		i;

	i = 0;
	if (!g_tracking.cpaste || !g_tracking.str)
		return ;
	if (ft_strlen(g_tracking.str) == 0)
		return ;
	g_tracking.cpaste->b1 = g_tracking.pos->abs;
	while (i == 0)
	{
		i = mini_read(0);
		g_tracking.cpaste->b2 = g_tracking.pos->abs;
		if (i == 7)
			break ;
		if (i == 8)
			ft_actual_cpy();
		print_line_cpy(g_tracking.cpaste->b1, g_tracking.cpaste->b2);
	}
	print_line();
	back_to_pos();
}
