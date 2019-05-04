/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_tab_to_exec.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjose <mjose@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/20 10:39:18 by mjose             #+#    #+#             */
/*   Updated: 2019/05/03 04:11:47 by mjose            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh42.h"

char	**expand_first_arg(char **tab_exec, int i, int *j, char **tab_farg)
{
	int		i_arg;

	i_arg = 0;
	if (tab_exec[0])
		tab_farg = ft_split_whitespaces(tab_exec[0]);
	if (tab_farg)
	{
		while (tab_farg[i_arg])
			i_arg++;
		if (i_arg > 1)
		{
			i_arg = tab_exec_arg(&tab_exec, &tab_farg, i_arg, i);
			*j = i_arg;
		}
		else
			*j = 1;
	}
	else
		*j = 1;
	free_tab(tab_farg);
	return (tab_exec);
}

char	**prepare_tab_to_expand(char **tab_exec, int *j, t_last *begin)
{
	int		i_arg;
	int		i;
	char	**tab_farg;

	i_arg = 0;
	tab_farg = NULL;
	g_tracking.mysh->in_ast = 0;
	g_tracking.mysh->err_expend = 0;
	i = *j;
	tab_exec = ft_memalloc(sizeof(char *) * (i + 1));
	tab_exec[0] = ft_strdup(begin->name);
	expand_transformer(&tab_exec[0], 1);
	tab_exec = expand_first_arg(tab_exec, i, j, tab_farg);
	return (tab_exec);
}

char	*assign_str(t_last *begin)
{
	char	*str;

	str = NULL;
	if (begin->type == OPT || begin->type == ARG)
	{
		str = ft_strdup(begin->name);
		expand_transformer(&str, 3);
	}
	return (str);
}

char	**create_tab_to_exec_h(t_last *begin, t_last *beginsave, int i)
{
	char		**tab_exec;

	if (beginsave != NULL)
		begin = beginsave;
	tab_exec = NULL;
	tab_exec = prepare_tab_to_expand(tab_exec, &i, begin);
	begin = begin->next;
	if (!tab_exec[0] && begin)
	{
		tab_exec[0] = ft_strdup(begin->name);
		begin = begin->next;
	}
	while (begin && begin->type != CMD)
	{
		if ((tab_exec[i] = assign_str(begin)))
			i++;
		begin = begin->next;
	}
	if (tab_exec)
		tab_exec[i] = NULL;
	g_tracking.mysh->in_ast = 1;
	if (beginsave != NULL)
		cmd_lstdel(beginsave);
	tab_exec = end_exec_tab(tab_exec);
	return (tab_exec);
}

char	**create_tab_to_exec(t_last *list)
{
	t_last		*begin;
	t_last		*beginsave;
	int			i;

	begin = list;
	beginsave = NULL;
	i = 1;
	list = list->next;
	while (list && list->type != CMD)
	{
		if (list->type == OPT || list->type == ARG)
			i++;
		list = list->next;
	}
	beginsave = tmp_local_vars(begin, begin);
	return (create_tab_to_exec_h(begin, beginsave, i));
}
