/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_to_lst.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abguimba <abguimba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/30 23:10:09 by bsiche            #+#    #+#             */
/*   Updated: 2019/03/20 06:11:03 by abguimba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh42.h"

t_keyval			*ft_env2(t_lstcontainer *split)
{
	t_keyval		*buf;
	t_list			*tmp;

	tmp = split->firstelement;
	buf = malloc(sizeof(*buf));
	buf->key = ft_strdup(tmp->content);
	buf->value = ft_strnew(0);
	tmp = tmp->next;
	while (tmp)
	{
		buf->value = ft_strjoinfree(buf->value, tmp->content, 1);
		tmp = tmp->next;
	}
	return (buf);
}

void				add_missing_string(void)
{
	char	*pwd;

	pwd = ft_true_pwd();
	if (get_env_string("PWD") == NULL)
		replace_env_str("PWD", pwd);
	ft_add_env_string("TRUEPWD", pwd);
	ft_add_env_string("TRUEOLDPWD", pwd);
	free(pwd);
}

t_lstcontainer		*ft_env_to_lst(char **environ)
{
	t_lstcontainer	*env;
	t_lstcontainer	*split;
	t_keyval		*buf;
	int				i;

	i = 0;
	env = NULL;
	env = lstcontainer_new();
	while (environ[i])
	{
		split = ft_strsplitlst(environ[i], '=');
		if (split != NULL)
		{
			buf = ft_env2(split);
			env->add(env, buf);
		}
		ft_freesplitlist(split);
		i++;
	}
	return (env);
}

t_lstcontainer		*copyenv(void)
{
	t_lstcontainer	*envcpy;
	t_list			*tmp;
	t_keyval		*buf;

	envcpy = lstcontainer_new();
	tmp = g_tracking.mysh->env->firstelement;
	while (tmp)
	{
		buf = malloc(sizeof(*buf));
		buf->key = ft_strdup(((t_keyval*)tmp->content)->key);
		buf->value = ft_strdup(((t_keyval*)tmp->content)->value);
		envcpy->add(envcpy, buf);
		tmp = tmp->next;
	}
	tmp = envcpy->firstelement;
	return (envcpy);
}

t_lstcontainer		*emptyenv(void)
{
	t_lstcontainer	*empty;
	t_list			*tmp;
	t_keyval		*buf;

	empty = lstcontainer_new();
	tmp = g_tracking.mysh->env->firstelement;
	while (tmp)
	{
		buf = malloc(sizeof(*buf));
		buf->key = ft_strdup(((t_keyval*)tmp->content)->key);
		if (ft_strcmp(buf->key, "PATH") == 0)
			buf->value = ft_strdup(((t_keyval*)tmp->content)->value);
		else
			buf->value = ft_strnew(0);
		empty->add(empty, buf);
		tmp = tmp->next;
	}
	return (empty);
}
