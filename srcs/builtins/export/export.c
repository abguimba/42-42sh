/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abguimba <abguimba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/15 12:52:33 by mjose             #+#    #+#             */
/*   Updated: 2019/05/01 07:20:04 by abguimba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh42.h"
#include "environ.h"
#include "builtins.h"

int			export_to_env(char *arg)
{
	char	*varname;
	char	*varvalue;

	varname = NULL;
	varvalue = NULL;
	if (is_new_value(arg))
		assign_to_env_save_value(varname, varvalue, arg);
	else if (ft_strchr(arg, '=') || !is_new_value(arg))
		assign_to_env_replace_value(varname, varvalue, arg);
	else if (!have_envname(varname))
		assign_to_env_if_not_exist(varname, varvalue, arg);
	else
	{
		ft_strdel(&arg);
		return (1);
	}
	ft_strdel(&arg);
	return (0);
}

void		print_export_env(void)
{
	t_list			*tmp;
	t_keyval		*buf;

	tmp = g_tracking.mysh->env->firstelement;
	buf = NULL;
	while (tmp)
	{
		buf = tmp->content;
		ft_putstr("export ");
		ft_putstr(buf->key);
		ft_putchar('=');
		ft_putchar('"');
		ft_putstr(buf->value);
		ft_putendl("\"");
		tmp = tmp->next;
	}
}

int			ft_export(void)
{
	char	**tab_arg;
	int		i;

	tab_arg = g_tracking.g_tab_exec;
	free_keyval(g_tracking.mysh->env);
	g_tracking.mysh->env = ft_env_to_lst(g_tracking.mysh->tab_env);
	i = 1;
	if (!tab_arg[i] || (ft_strequ(tab_arg[i], "-p") && !tab_arg[i + 1]))
	{
		print_export_env();
		return (0);
	}
	while (tab_arg[i])
	{
		if (ft_strequ(tab_arg[i], "-p"))
			i++;
		if (tab_arg[i][0] == '=')
			return (export_error(tab_arg[i]));
		if (export_to_env(ft_strdup(tab_arg[i])))
			return (export_error(tab_arg[i]));
		i++;
	}
	return (0);
}
