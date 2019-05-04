/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_cmd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsiche <bsiche@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/12 03:05:45 by bsiche            #+#    #+#             */
/*   Updated: 2019/05/04 02:16:09 by bsiche           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh42.h"

void	ft_return(void)
{
	g_tracking.cmd = ft_strdup(g_tracking.str);
	ft_strdel(&g_tracking.str);
	ft_strdel(&g_tracking.cpaste->line);
	g_tracking.str = NULL;
	if (g_tracking.tmp_hist)
		ft_strdel(&g_tracking.tmp_hist);
	cursor_reset();
}

void	left_right(char *str)
{
	if (ft_strcmp(str, K_LEFT) == 0)
		move_left();
	if (ft_strcmp(str, K_RIGHT) == 0)
		move_right();
}

void	home_end(char *str)
{
	if (ft_strcmp(str, K_HOME) == 0)
		go_home();
	if (ft_strcmp(str, K_END) == 0)
		go_end();
}

int		ft_exec_key(char *str)
{
	if (ft_strcmp(str, K_HOME) == 0 || ft_strcmp(str, K_END) == 0)
		home_end(str);
	if (ft_strcmp(str, K_LEFT) == 0 || ft_strcmp(str, K_RIGHT) == 0)
		left_right(str);
	if (ft_strcmp(str, K_WRIGHT) == 0)
		next_word();
	if (ft_strcmp(str, K_WLEFT) == 0)
		prev_word();
	if (ft_strcmp(str, K_LUP) == 0)
		move_up();
	if (ft_strcmp(str, K_LDOWN) == 0)
		move_down();
	if (ft_strcmp(str, K_DEL) == 0)
		rem_from_str_del();
	if (ft_strcmp(str, K_FN1) == 0)
		begin_cpy();
	if (ft_strcmp(str, K_FN3) == 0)
		begin_paste();
	if (ft_strcmp(str, K_UP) == 0)
		history_up();
	if (ft_strcmp(str, K_DOWN) == 0)
		history_down();
	return (6);
}

int		is_cmd(char *str)
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
			return (ft_exec_key(str));
		tmp = tmp->next;
	}
	if (flag == 0)
		return (7);
	return (0);
}
