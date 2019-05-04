/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fc_oldnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsiche <bsiche@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/26 01:28:13 by bsiche            #+#    #+#             */
/*   Updated: 2019/05/04 03:21:49 by bsiche           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh42.h"

int		eq_sign(char *str)
{
	int		i;
	int		flag;

	i = 0;
	flag = 0;
	if (!str)
		return (0);
	while (str[i])
	{
		if (str[i] == '=')
			flag = 1;
		i++;
	}
	return (flag);
}

char	*quote_remove(char *tmp)
{
	int		i;
	int		a;
	char	*new;

	i = 0;
	a = 0;
	if (!tmp)
		return (NULL);
	new = ft_strnew(ft_strlen(tmp) + 1);
	while (tmp[i])
	{
		if (tmp[i] != '"' && tmp[i] != '\'')
		{
			new[a] = tmp[i];
			a++;
		}
		i++;
	}
	new[a] = '\0';
	ft_strdel(&tmp);
	return (new);
}

void	get_keyval(t_fcparse *opt)
{
	t_lstcontainer	*list;
	t_list			*tmp;

	list = ft_strsplitlst(opt->first, '=');
	if (!list || !list->firstelement || !list->firstelement->next)
		return ;
	ft_free(opt->first);
	tmp = list->firstelement;
	opt->first = ft_strdup(tmp->content);
	tmp = tmp->next;
	if (!tmp)
		return ;
	ft_free(opt->last);
	opt->last = ft_strdup(tmp->content);
	ft_freesplitlist(list);
}

char	*ft_swap_fc(char *tmp, t_fcparse *opt)
{
	t_lstcontainer	*list;

	if (!tmp || !opt)
		return (NULL);
	get_keyval(opt);
	if (!opt->first || !opt->last)
		return (NULL);
	tmp = quote_remove(tmp);
	if (!tmp)
		return (NULL);
	list = ft_split_with_char(tmp);
	ft_strdel(&tmp);
	if (list)
		swap_list(list, opt);
	tmp = rebuild_line(list);
	return (tmp);
}

int		create_fc_oldnew(t_fcparse *opt)
{
	int		flag;
	t_list	*tmp;
	char	*cmd;

	if (!opt || !g_tracking.mysh || !g_tracking.mysh->hist
		|| !g_tracking.mysh->hist->firstelement)
		return (-1);
	flag = 0;
	if (opt->low == -4)
		flag = 1;
	get_neg_offset(opt);
	tmp = ft_lstget(opt->max, g_tracking.mysh->hist->firstelement);
	cmd = ft_strdup(tmp->content);
	if (flag == 1)
	{
		if (!opt->first)
			fc_error(5, NULL);
		if (eq_sign(opt->first) > 1)
			fc_error(5, NULL);
		cmd = ft_swap_fc(cmd, opt);
	}
	ft_putendl_fd(cmd, 2);
	main_loop(cmd);
	ft_strdel(&cmd);
	return (0);
}
