/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helpers.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjose <mjose@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/10 15:02:07 by mjose             #+#    #+#             */
/*   Updated: 2019/05/01 22:50:43 by bsiche           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh42.h"

char	**convert_backtab(char **taab)
{
	int		i;

	i = 0;
	while (taab[i])
	{
		taab[i] = convert_back(taab[i]);
		taab[i] = remove_back(taab[i], 0);
		i++;
	}
	return (taab);
}

int		tab_exec_arg(char ***tab_exec, char ***tab_farg, int i_arg, int i)
{
	char	**run_texec;
	char	**run_tfarg;

	run_texec = *tab_exec;
	run_tfarg = *tab_farg;
	free_tab(run_texec);
	run_texec = ft_memalloc(sizeof(char *) * (i + i_arg + 1));
	i_arg = 0;
	while (run_tfarg[i_arg])
	{
		run_texec[i_arg] = ft_strdup(run_tfarg[i_arg]);
		i_arg++;
	}
	*tab_exec = run_texec;
	return (i_arg);
}

void	recup_last_arg(char **tab_exec)
{
	int		i;

	i = 0;
	if (!tab_exec || !tab_exec[i] || !tab_exec[i][0]
			|| g_tracking.mysh->err_expend)
		return ;
	while (tab_exec[i])
	{
		replace_env_str("_", tab_exec[i++]);
		update_envp();
	}
}

char	**end_exec_tab(char **tab_exec)
{
	tab_exec = convert_backtab(tab_exec);
	recup_last_arg(tab_exec);
	return (tab_exec);
}
