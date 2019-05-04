/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_environ.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsiche <bsiche@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/07 16:38:46 by mjose             #+#    #+#             */
/*   Updated: 2019/04/22 03:21:18 by bsiche           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh42.h"

int			have_setname(char *var)
{
	t_list		*set_env;
	t_keyval	*buf;

	if (!g_tracking.mysh->set_env)
		return (0);
	set_env = g_tracking.mysh->set_env->firstelement;
	while (set_env)
	{
		buf = set_env->content;
		if (ft_strcmp(var, buf->key) == 0)
			return (2);
		set_env = set_env->next;
	}
	return (0);
}

char		*remove_set_env_string(char *str)
{
	t_list		*tmp;
	t_keyval	*buf;

	if (g_tracking.mysh->set_env == NULL)
		return (NULL);
	tmp = g_tracking.mysh->set_env->firstelement;
	while (tmp)
	{
		buf = tmp->content;
		if (ft_strcmp(str, buf->key) == 0)
		{
			ft_strdel(&buf->key);
			ft_strdel(&buf->value);
			g_tracking.mysh->set_env->remove(g_tracking.mysh->set_env, tmp, 1);
			return (NULL);
		}
		tmp = tmp->next;
	}
	return (NULL);
}

char		*get_set_env_string(char *str)
{
	t_list		*tmp;
	t_keyval	*buf;

	if (g_tracking.mysh->set_env == NULL)
		return (NULL);
	tmp = g_tracking.mysh->set_env->firstelement;
	while (tmp)
	{
		buf = tmp->content;
		if (ft_strcmp(str, buf->key) == 0)
			return (buf->value);
		tmp = tmp->next;
	}
	return (NULL);
}

void		replace_env_set_str(char *s1, char *s2)
{
	t_list		*tmp;
	t_keyval	*buf;

	if (g_tracking.mysh->set_env == NULL)
	{
		ft_add_setenv_string(s1, s2);
		return ;
	}
	tmp = g_tracking.mysh->set_env->firstelement;
	while (tmp)
	{
		buf = tmp->content;
		if (ft_strcmp(s1, buf->key) == 0)
		{
			ft_free(buf->value);
			buf->value = ft_strdup(s2);
			return ;
		}
		tmp = tmp->next;
	}
	ft_add_setenv_string(s1, s2);
}

void		ft_add_setenv_string(char *s1, char *s2)
{
	t_keyval	*buf;

	if (g_tracking.mysh->set_env == NULL)
		g_tracking.mysh->set_env = lstcontainer_new();
	buf = ft_malloc(sizeof(*buf));
	buf->value = NULL;
	buf->key = NULL;
	buf->key = ft_strdup(s1);
	buf->value = ft_strdup(s2);
	buf->loop = 0;
	g_tracking.mysh->set_env->add(g_tracking.mysh->set_env, buf);
}
