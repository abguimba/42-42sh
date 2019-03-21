/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   next_word.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abguimba <abguimba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/03 00:52:42 by bsiche            #+#    #+#             */
/*   Updated: 2019/03/20 06:11:03 by abguimba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/sh42.h"

int		is_space(char c)
{
	if (c == ' ' || c == '\t' || c == ';' || c == '\0')
		return (1);
	else
		return (0);
}

void	print_and_go(int i)
{
	print_line();
	g_tracking.pos->abs = rev_utf_goto(g_tracking.str, (i));
	back_to_pos();
}

void	next_word(void)
{
	char	*tmp;
	int		i;

	i = utf_goto(g_tracking.str, g_tracking.pos->abs);
	tmp = g_tracking.str;
	if (tmp != NULL)
	{
		while (tmp[i] && tmp[i] < g_tracking.buffsize)
		{
			if (is_space(tmp[i]) == 0)
				i++;
			else
			{
				while (is_space(tmp[i]) == 1)
					i++;
				break ;
			}
		}
		print_and_go(i);
	}
}

void	move_back(char *tmp, int i)
{
	if (tmp[i] == '\0')
		i--;
	if (tmp[i] != '\0' && is_space(tmp[i]) == 0 && i != 0)
		i--;
	if (tmp[i] != '\0' && is_space(tmp[i]) == 1 && i != 0)
	{
		while (tmp[i] != '\0' && is_space(tmp[i]) == 1 && i != 0)
			i--;
	}
	while (tmp[i] && i != 0)
	{
		while (tmp[i] != '\0' && is_space(tmp[i]) == 0 && i != 0)
			i--;
		break ;
	}
	if (i < 1)
		i = -1;
	i++;
	print_and_go(i);
}

void	prev_word(void)
{
	char	*tmp;
	int		i;

	i = utf_goto(g_tracking.str, g_tracking.pos->abs);
	tmp = g_tracking.str;
	if (tmp != NULL && i != 0)
		move_back(tmp, i);
}
