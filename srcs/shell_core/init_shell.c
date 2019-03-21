/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_shell.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abguimba <abguimba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/17 23:10:27 by bsiche            #+#    #+#             */
/*   Updated: 2019/03/20 06:11:03 by abguimba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh42.h"

void	ft_printlist(void)
{
	t_list			*tmp;
	t_keyval		*buf;

	tmp = g_tracking.mysh->env->firstelement;
	buf = NULL;
	while (tmp)
	{
		buf = tmp->content;
		ft_putstr(buf->key);
		ft_putchar('=');
		ft_putendl(buf->value);
		tmp = tmp->next;
	}
}

void	init_global(void)
{
	g_tracking.builtin = 0;
	g_tracking.jobs = NULL;
	g_tracking.lastreturn = 0;
	g_tracking.mysh->hist = NULL;
	g_tracking.mysh->alias_lst = NULL;
}

void	init_shell(char **environ)
{
	t_shell		*mysh;
	int			i;

	i = 0;
	if (!(mysh = malloc(sizeof(t_shell))))
	{
		ft_putendl("Failled to allocate memory");
		exit(EXIT_FAILURE);
	}
	while (i < 27)
	{
		g_tracking.hashtable[i] = NULL;
		i++;
	}
	g_tracking.mysh = mysh;
	init_global();
	init_alias();
	g_tracking.mysh->env = ft_env_to_lst(environ);
	g_tracking.mysh->hist = NULL;
	add_missing_string();
	hist_file_to_lst();
	g_tracking.mysh->tab_env = init_envp(g_tracking.mysh->env);
	g_tracking.mysh->setenv_lst = NULL;
	g_tracking.mysh->expand_error = 0;
	g_tracking.quotes = 0;
}
