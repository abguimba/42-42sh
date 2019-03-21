/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   var_list.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abguimba <abguimba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/18 20:45:18 by bsiche            #+#    #+#             */
/*   Updated: 2019/03/20 06:11:03 by abguimba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh42.h"

t_ls				*ls_alloc(char *str)
{
	t_ls			*info;

	info = malloc(sizeof(t_ls) + 1);
	info->name = ft_strdup(str);
	info->path = NULL;
	info->symlink = NULL;
	info->strusrname = NULL;
	info->strgroup = NULL;
	info->strlink = NULL;
	info->strtime = NULL;
	info->strpermission = ft_strdup("---------");
	info->strsize = NULL;
	info->strmin = NULL;
	info->strmaj = NULL;
	info->strpad = NULL;
	info->timeswitch = 0;
	info->color = 0;
	info->issimple = 1;
	return (info);
}

void				build_var_lst(void)
{
	t_list			*buf;
	t_keyval		*tmp;
	t_ls			*new;

	buf = g_tracking.mysh->env->firstelement;
	if (!buf)
		return ;
	g_tracking.aut->var_lst = lstcontainer_new();
	while (buf)
	{
		tmp = buf->content;
		new = ls_alloc(tmp->key);
		lstcontainer_add(g_tracking.aut->var_lst, new);
		buf = buf->next;
	}
}
