/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hash_args.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abguimba <abguimba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/15 12:52:33 by mjose             #+#    #+#             */
/*   Updated: 2019/05/02 02:57:54 by abguimba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh42.h"

void		hash_update_helper(t_hash *tmp, int index, int j, char **c)
{
	char	**hold;

	hold = g_tracking.g_tab_exec;
	index = ft_tolower(hold[j][0]) - 'a';
	tmp = g_tracking.hashtable[index];
	while (tmp)
	{
		if (!(ft_strcmp(hold[j], tmp->binary)))
		{
			ft_strdel(&tmp->path);
			tmp->path = ft_strdup(c[0]);
			tmp->totalhits = 0;
			break ;
		}
		if (!tmp->nextbinary)
			break ;
		tmp = tmp->nextbinary;
	}
	if (tmp)
	{
		if (!tmp->nextbinary && ft_strcmp(hold[j], tmp->binary))
			tmp->nextbinary = new_binary_hash(hold[j], c[0], 0);
	}
	else
		g_tracking.hashtable[index] = new_binary_hash(hold[j], c[0], 0);
}

void		ft_hash_output_helper(t_hash *tmp, int spaces)
{
	int		totalhitshold;

	while (tmp)
	{
		spaces = 3;
		totalhitshold = tmp->totalhits;
		while (totalhitshold / 10)
		{
			totalhitshold = totalhitshold / 10;
			spaces -= 1;
		}
		while (spaces-- > 0)
			ft_putchar(' ');
		ft_putnbr(tmp->totalhits);
		ft_putstr("    ");
		ft_putendl(tmp->path);
		tmp = tmp->nextbinary;
	}
}

int			ft_hash_arg(int j)
{
	while (g_tracking.g_tab_exec[j] && g_tracking.g_tab_exec[j][0] == '-')
	{
		if (ft_strchr(g_tracking.g_tab_exec[j], 'r'))
		{
			empty_hash_table();
			if (!(g_tracking.g_tab_exec[j + 1]))
				return (0);
		}
		if (g_tracking.g_tab_exec[j] && g_tracking.g_tab_exec[j][1] != 'r')
			errors_hash(g_tracking.g_tab_exec[j], 2);
		j++;
	}
	if (g_tracking.g_tab_exec[j])
		return (hash_update_commands(j));
	return (0);
}
