/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsiche <bsiche@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/21 02:58:02 by bsiche            #+#    #+#             */
/*   Updated: 2019/05/02 09:10:36 by bsiche           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh42.h"

int		offset_error(void)
{
	ft_putendl_fd("Usage : History [-d] [offset]", 2);
	return (1);
}

int		history_offset(char **av)
{
	int		i;
	t_list	*tmp;
	t_list	*next;

	if (av[1])
	{
		if (!av[2] || ft_isinteg(av[2]) != 0 || !g_tracking.mysh->hist)
			return (offset_error());
		i = ft_atoi(av[2]);
		tmp = ft_lstget(i, g_tracking.mysh->hist->firstelement);
		while (tmp)
		{
			next = tmp->next;
			lstcontainer_remove(g_tracking.mysh->hist, tmp, 1);
			tmp = next;
		}
		return (0);
	}
	return (1);
}

int		history_builtin(void)
{
	char	**av;

	av = g_tracking.g_tab_exec;
	if (!av[1])
	{
		print_history();
		return (0);
	}
	if (ft_strcmp(av[1], "-d") == 0)
		return (history_offset(av));
	if (ft_strcmp(av[1], "-c") == 0)
	{
		free_hist();
		g_tracking.mysh->hist = lstcontainer_new();
		return (0);
	}
	return (0);
}
