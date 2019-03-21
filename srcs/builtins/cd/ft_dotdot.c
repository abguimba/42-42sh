/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dotdot.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsiche <bsiche@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/06 03:47:41 by bsiche            #+#    #+#             */
/*   Updated: 2019/03/05 04:02:44 by bsiche           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh42.h"

char		*dotdot2(t_lstcontainer *new)
{
	char	*path;
	t_list	*buf;

	path = ft_strnew(0);
	if (new->firstelement != NULL)
	{
		buf = new->firstelement;
		while (buf)
		{
			path = ft_strjoinfree(path, "/", 1);
			path = ft_strjoinfree(path, buf->content, 1);
			buf = buf->next;
		}
	}
	if (ft_strlen(path) == 0)
	{
		free(path);
		path = ft_strdup("/");
	}
	return (path);
}

char		*ft_dotdot(t_lstcontainer *new)
{
	char	*path;
	t_list	*buf;

	buf = new->firstelement;
	while (buf)
	{
		if (ft_strcmp(buf->content, "..") == 0)
		{
			new->remove(new, buf, 0);
			new->remove(new, buf->prev, 0);
		}
		buf = buf->next;
	}
	path = dotdot2(new);
	return (path);
}

char		*ft_dot(char *path)
{
	t_lstcontainer	*new;
	t_list			*buf;

	new = ft_strsplitlst(path, '/');
	if (new != NULL)
	{
		buf = new->firstelement;
		while (buf)
		{
			if (ft_strcmp(buf->content, ".") == 0)
				new->remove(new, buf, 0);
			buf = buf->next;
		}
		free(path);
		path = ft_dotdot(new);
		ft_freesplitlist(new);
	}
	return (path);
}
