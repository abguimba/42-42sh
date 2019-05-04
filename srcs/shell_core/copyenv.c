/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   copyenv.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsiche <bsiche@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/26 18:55:40 by bsiche            #+#    #+#             */
/*   Updated: 2019/04/22 02:52:18 by bsiche           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh42.h"

void	ft_printab(char **taab)
{
	int i;

	i = 0;
	while (taab[i])
	{
		ft_putendl(taab[i]);
		i++;
	}
}

char	*get_env_string(char *str)
{
	t_list		*tmp;
	t_keyval	*buf;

	if (g_tracking.mysh->env == NULL)
		return (NULL);
	tmp = g_tracking.mysh->env->firstelement;
	while (tmp)
	{
		buf = tmp->content;
		if (ft_strcmp(str, buf->key) == 0)
			return (buf->value);
		tmp = tmp->next;
	}
	return (NULL);
}

int		replace_env_str(char *s1, char *s2)
{
	t_list		*tmp;
	t_keyval	*buf;

	if (g_tracking.mysh->env == NULL)
	{
		ft_add_env_string(s1, s2);
		return (0);
	}
	tmp = g_tracking.mysh->env->firstelement;
	while (tmp)
	{
		buf = tmp->content;
		if (ft_strcmp(s1, buf->key) == 0)
		{
			ft_free(buf->value);
			buf->value = ft_strdup(s2);
			return (0);
		}
		tmp = tmp->next;
	}
	ft_add_env_string(s1, s2);
	return (0);
}

void	ft_add_env_string(char *s1, char *s2)
{
	t_keyval	*buf;

	if (g_tracking.mysh->env == NULL)
		g_tracking.mysh->env = lstcontainer_new();
	buf = ft_malloc(sizeof(*buf));
	buf->value = NULL;
	buf->key = NULL;
	buf->key = ft_strdup(s1);
	buf->value = ft_strdup(s2);
	buf->loop = 0;
	g_tracking.mysh->env->add(g_tracking.mysh->env, buf);
}

char	*remove_env_string(char *str)
{
	t_list		*tmp;
	t_keyval	*buf;

	if (g_tracking.mysh->env == NULL)
		return (NULL);
	tmp = g_tracking.mysh->env->firstelement;
	while (tmp)
	{
		buf = tmp->content;
		if (ft_strcmp(str, buf->key) == 0)
		{
			ft_strdel(&buf->key);
			ft_strdel(&buf->value);
			g_tracking.mysh->env->remove(g_tracking.mysh->env, tmp, 1);
			return (NULL);
		}
		tmp = tmp->next;
	}
	return (NULL);
}
