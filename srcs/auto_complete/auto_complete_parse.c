/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   auto_complete_parse.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsiche <bsiche@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/18 20:45:18 by bsiche            #+#    #+#             */
/*   Updated: 2019/05/01 02:19:56 by bsiche           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh42.h"

void	escape_path(void)
{
	t_lstcontainer	*tmp;
	t_list			*buf;
	char			*string;

	tmp = NULL;
	tmp = ft_strsplitlst(g_tracking.aut->to_add, ' ');
	if (lstcontainer_size(tmp) > 1)
	{
		string = ft_strnew(0);
		buf = tmp->firstelement;
		while (buf)
		{
			string = ft_strjoinfree(string, buf->content, 1);
			if (buf->next)
				string = ft_strjoinfree(string, "\\ ", 1);
			buf = buf->next;
		}
		ft_free(g_tracking.aut->to_add);
		g_tracking.aut->to_add = string;
	}
	ft_freesplitlist(tmp);
	g_tracking.aut->to_add = ft_strjoinfree(g_tracking.aut->to_add, "/", 1);
}

void	rm_slash(void)
{
	t_lstcontainer		*tmp;
	t_list				*buf;
	int					i;

	i = 0;
	while (g_tracking.aut->word[i])
		i++;
	if (i > 0)
	{
		i--;
		if (g_tracking.aut->word[i] == '/')
			ft_strdel(&g_tracking.aut->word);
	}
	if (g_tracking.aut->word)
	{
		tmp = ft_strsplitlst(g_tracking.aut->word, '/');
		if (tmp != NULL)
		{
			buf = ft_lstgetlast(tmp->firstelement);
			ft_strdel(&g_tracking.aut->word);
			g_tracking.aut->word = ft_strdup(buf->content);
			ft_freesplitlist(tmp);
		}
	}
}

int		sanitize_path(void)
{
	int		i;
	int		a;
	char	*path;

	if (g_tracking.aut->word[0] == '~' || g_tracking.aut->word[0] == '$')
		g_tracking.aut->word = ft_exp_complete(g_tracking.aut->word);
	if (!g_tracking.aut->word)
		return (0);
	i = ft_strlen(g_tracking.aut->word);
	a = 0;
	while (g_tracking.aut->word[i] != '/' && i > 0)
		i--;
	path = ft_strnew(i);
	while (i > a)
	{
		path[a] = g_tracking.aut->word[a];
		a++;
	}
	path = ft_strjoinfree(path, "/", 1);
	if (g_tracking.aut->path)
		ft_strdel(&g_tracking.aut->path);
	g_tracking.aut->path = path;
	return (0);
}

void	assign_type(void)
{
	int i;

	i = 0;
	g_tracking.aut->path = NULL;
	if (g_tracking.aut->word != NULL)
	{
		g_tracking.aut->type = check_type();
		if (g_tracking.aut->type == 1)
		{
			g_tracking.aut->path = ft_strdup(g_tracking.aut->word);
			sanitize_path();
			rm_slash();
		}
		if (g_tracking.aut->type == 2)
		{
			i = ft_strlen(g_tracking.aut->word);
			g_tracking.aut->word = ft_strsub(g_tracking.aut->word, 2, i, 1);
			complete_usr_var();
		}
	}
	check_hidden();
}
