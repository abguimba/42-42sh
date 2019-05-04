/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   recursive.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjose <mjose@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/15 00:23:13 by bsiche            #+#    #+#             */
/*   Updated: 2019/04/18 02:10:31 by mjose            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh42.h"

void			free_null(char *str)
{
	ft_free(str);
	str = NULL;
}

void			ft_freestruct(t_list *liste)
{
	t_list	*buf;
	t_ls	*tmp;

	buf = ft_lstgetfirst(liste);
	while (buf != NULL)
	{
		tmp = buf->content;
		free_null(tmp->name);
		free_null(tmp->strlink);
		free_null(tmp->path);
		free_null(tmp->strusrname);
		free_null(tmp->strgroup);
		free_null(tmp->strsize);
		free_null(tmp->strmaj);
		free_null(tmp->strmin);
		free_null(tmp->strtime);
		free_null(tmp->strpermission);
		free_null(tmp->symlink);
		free_null(tmp->strpad);
		ft_free(buf->content);
		buf->content = NULL;
		buf = buf->next;
	}
}
