/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_three.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abguimba <abguimba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/10 15:02:07 by mjose             #+#    #+#             */
/*   Updated: 2019/05/02 03:06:21 by abguimba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh42.h"

void		execute_three(char **tab_exec, char **tab_exec_hold, char *p)
{
	char	**envhold;

	apply_env();
	envhold = init_envp(g_tracking.mysh->env);
	execve(p, tab_exec, init_envp(g_tracking.mysh->env));
	ft_strdel(&p);
	free_tabs_and_exit(envhold, tab_exec_hold);
}
