/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_fc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsiche <bsiche@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/21 04:44:37 by bsiche            #+#    #+#             */
/*   Updated: 2019/05/04 03:20:50 by bsiche           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh42.h"

void	save_to_hist(t_fcparse *opt)
{
	int		i;

	if (!opt)
		return ;
	if (write(0, "c", 0) != -1)
	{
		i = ft_strlen(opt->shist);
		if (ft_strcmp(opt->shist, "\n") != 0 && i > 0 && opt->shist[0] > 32)
			lstcontainer_add(g_tracking.mysh->hist, ft_strdup(opt->shist));
	}
}

void	hist_set_unset(int i, t_fcparse *opt)
{
	t_list	*tmp;

	if (!g_tracking.mysh || !g_tracking.mysh->hist || !opt)
		return ;
	if (i == 0)
	{
		tmp = ft_lstgetlast(g_tracking.mysh->hist->lastelement);
		g_tracking.mysh->hist->lastelement = tmp->prev;
		if (opt->shist)
			ft_strdel(&opt->shist);
		opt->shist = ft_strdup(tmp->content);
		lstcontainer_remove(g_tracking.mysh->hist, tmp, 1);
		tmp = NULL;
	}
	if (i == 1)
	{
		if (!opt || opt->e == 1 || opt->s == 1)
			return ;
		else
			save_to_hist(opt);
	}
}

void	free_opt(t_fcparse *opt)
{
	if (!opt)
		return ;
	ft_strdel(&opt->editor);
	ft_strdel(&opt->first);
	ft_strdel(&opt->last);
	ft_strdel(&opt->shist);
	ft_strdel(&opt->str);
	ft_free(opt);
}

int		dup_func(int i)
{
	if (i == 1)
	{
		if (dup2(10, g_tracking.mysh->dup1) == -1)
			return (-1);
		if (dup2(11, g_tracking.mysh->dup2) == -1)
			return (-1);
		if (dup2(12, g_tracking.mysh->dup3) == -1)
			return (-1);
	}
	if (i == 2)
	{
		if (dup2(g_tracking.mysh->dup1, 10) == -1)
			return (-1);
		close(g_tracking.mysh->dup1);
		if (dup2(g_tracking.mysh->dup2, 11) == -1)
			return (-1);
		close(g_tracking.mysh->dup2);
		if (dup2(g_tracking.mysh->dup3, 12) == -1)
			return (-1);
		close(g_tracking.mysh->dup3);
	}
	return (0);
}

int		fc_builtin(void)
{
	char		**av;
	int			count;
	t_fcparse	*opt;

	if (g_tracking.fc == 0)
		dup_func(1);
	count = 0;
	av = g_tracking.g_tab_exec;
	g_tracking.fc++;
	opt = (fc_option(av, 1));
	hist_set_unset(0, opt);
	while (av[count])
		count++;
	if (opt->i > count || (opt = fc_offset(av, opt)) == NULL)
		return (1);
	if (opt->err != 0)
		fc_error(2, NULL);
	char_to_index(opt);
	fc_mode(opt);
	free_opt(opt);
	g_tracking.fc--;
	if (g_tracking.fc == 0)
		dup_func(2);
	return (0);
}
