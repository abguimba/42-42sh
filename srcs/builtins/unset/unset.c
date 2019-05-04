/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abguimba <abguimba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/15 12:52:33 by mjose             #+#    #+#             */
/*   Updated: 2019/05/01 07:15:51 by abguimba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh42.h"
#include "environ.h"

int			ft_unset(void)
{
	char	**taab;
	int		i;

	taab = g_tracking.g_tab_exec;
	i = 1;
	free_keyval(g_tracking.mysh->env);
	g_tracking.mysh->env = ft_env_to_lst(g_tracking.mysh->tab_env);
	while (taab[i])
		remove_env_string(taab[i++]);
	update_envp();
	i = 1;
	while (taab[i])
		remove_set_env_string(taab[i++]);
	return (0);
}
