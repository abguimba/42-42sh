/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_sh.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abguimba <abguimba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/12 05:43:44 by mjose             #+#    #+#             */
/*   Updated: 2019/05/02 01:30:55 by abguimba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh42.h"

int		exec_sh(void)
{
	char	**envhold;
	char	**tab_exec_hold;

	apply_env();
	envhold = init_envp(g_tracking.mysh->env);
	tab_exec_hold = (char **)ft_malloc(sizeof(char *) * 3);
	tab_exec_hold[0] = ft_strdup("sh");
	tab_exec_hold[1] = ft_strdup(g_tracking.g_tab_exec[0]);
	tab_exec_hold[2] = NULL;
	execve("/bin/sh", tab_exec_hold, envhold);
	free_tabs_and_exit(envhold, tab_exec_hold);
	return (-1);
}
