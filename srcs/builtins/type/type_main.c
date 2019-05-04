/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   type_main.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abguimba <abguimba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/23 00:07:42 by bsiche            #+#    #+#             */
/*   Updated: 2019/05/03 04:06:18 by abguimba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh42.h"

int		type_error(char *cmd)
{
	char	*err;

	err = ft_strdup("command ");
	err = ft_strjoinfree(err, cmd, 1);
	err = ft_strjoinfree(err, " not found", 1);
	ft_putendl_fd(err, 2);
	ft_free(err);
	err = NULL;
	return (1);
}

int		exist_builtin(char *cmd)
{
	t_list	*tmp;

	tmp = NULL;
	if (!g_tracking.builtin_list)
		return (0);
	tmp = g_tracking.builtin_list->firstelement;
	if (!tmp || !cmd)
		return (0);
	if (!ft_strcmp(cmd, ".."))
		return (0);
	while (tmp)
	{
		if (ft_strcmp(cmd, tmp->content) == 0)
			return (1);
		tmp = tmp->next;
	}
	return (0);
}

int		type_check(char *cmd)
{
	char	*dummy;
	int		flag;

	flag = 0;
	dummy = NULL;
	if (return_alias(cmd) != NULL)
		return (1);
	if (exist_builtin(cmd) != 0)
		return (1);
	dummy = exist_fonction(cmd);
	if (dummy)
		flag = 1;
	ft_free(dummy);
	return (flag);
}

int		type_print(char *cmd)
{
	char	*dummy;
	int		flag;

	dummy = NULL;
	flag = 0;
	dummy = ft_strdup(cmd);
	dummy = ft_strjoinfree(dummy, " is ", 1);
	if (return_alias(cmd) != NULL)
	{
		dummy = ft_strjoinfree(dummy, "aliased to ", 1);
		dummy = ft_strjoinfree(dummy, return_alias(cmd), 1);
		flag = 1;
	}
	if (flag != 1 && exist_builtin(cmd) == 1)
	{
		dummy = ft_strjoinfree(dummy, "a shell builtin", 1);
		flag = 1;
	}
	if (flag == 0)
		dummy = ft_strjoinfree(dummy, exist_fonction(cmd), 3);
	if (dummy)
		ft_putendl(dummy);
	ft_strdel(&dummy);
	return (0);
}

int		type_main(void)
{
	char	**av;
	int		i;

	i = 1;
	av = g_tracking.g_tab_exec;
	if (!av)
		return (1);
	while (av[i])
	{
		if ((type_check(av[i]) != 1))
			return (type_error(av[i]));
		i++;
	}
	i = 1;
	while (av[i])
	{
		type_print(av[i]);
		i++;
	}
	return (0);
}
