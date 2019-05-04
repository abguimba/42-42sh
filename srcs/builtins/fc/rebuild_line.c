/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rebuild_line.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsiche <bsiche@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/27 19:56:33 by bsiche            #+#    #+#             */
/*   Updated: 2019/05/01 06:54:15 by bsiche           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh42.h"

void	swap_list(t_lstcontainer *list, t_fcparse *opt)
{
	t_list	*buf;

	if (!list || !list->firstelement || !opt)
		return ;
	buf = ft_lstgetfirst(list->firstelement);
	while (buf)
	{
		if (ft_strcmp(buf->content, opt->first) == 0)
		{
			ft_free(buf->content);
			buf->content = ft_strdup(opt->last);
		}
		buf = buf->next;
	}
}

char	*rebuild_line(t_lstcontainer *list)
{
	char	*new;
	t_list	*tmp;

	if (!list)
		return (NULL);
	tmp = ft_lstgetfirst(list->firstelement);
	new = NULL;
	while (tmp)
	{
		new = ft_strjoinfree(new, tmp->content, 1);
		tmp = tmp->next;
	}
	ft_freesplitlist(list);
	return (new);
}
