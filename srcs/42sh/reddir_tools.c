/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reddir_tools.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsiche <bsiche@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/07 02:22:33 by mjose             #+#    #+#             */
/*   Updated: 2019/05/03 08:07:33 by bsiche           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh42.h"

int		clean_reddir(char ***tab_reddir)
{
	restore_fd();
	free_tab(g_tracking.g_tab_exec);
	g_tracking.g_tab_exec = NULL;
	restore_env();
	free_tab(*tab_reddir);
	return (0);
}

char	**create_tab_reddir(t_last **list)
{
	int		i;
	char	**tab_reddir;

	i = 0;
	tab_reddir = ft_memalloc(sizeof(char *) * 3);
	tab_reddir[i] = ft_strdup((*list)->name);
	tab_reddir[i] = convert_back(tab_reddir[i]);
	tab_reddir[i] = remove_back(tab_reddir[i], 0);
	i++;
	if ((*list)->next && (*list)->next->name)
	{
		tab_reddir[i] = ft_strdup((*list)->next->name);
		tab_reddir[i] = convert_back(tab_reddir[i]);
		tab_reddir[i] = remove_back(tab_reddir[i], 0);
		i++;
	}
	tab_reddir[i] = NULL;
	return (tab_reddir);
}

char	**add_to_tab_reddir(t_last **list, char ***tab_reddir)
{
	int		i;
	char	**new_tab;

	i = 0;
	new_tab = NULL;
	while ((*tab_reddir)[i])
		i++;
	new_tab = ft_memalloc(sizeof(char *) * (i + 3));
	i = 0;
	while ((*tab_reddir)[i])
	{
		new_tab[i] = assign_reddir((*tab_reddir)[i]);
		i++;
	}
	new_tab[i] = assign_reddir((*list)->name);
	i++;
	if ((*list)->next && (*list)->next->name)
	{
		new_tab[i] = assign_reddir((*list)->next->name);
		i++;
	}
	new_tab[i] = NULL;
	free_tab(*tab_reddir);
	tab_reddir = NULL;
	return (new_tab);
}

void	save_reddir(t_last **list, char ***tab_reddir)
{
	if ((*tab_reddir) == NULL)
		*tab_reddir = create_tab_reddir(list);
	else
		*tab_reddir = add_to_tab_reddir(list, tab_reddir);
}

void	execute_reddir(char ***tab_reddir)
{
	make_reddir(*tab_reddir, 0);
	free_tab(*tab_reddir);
	*tab_reddir = NULL;
	g_tracking.mysh->tab_reddir = NULL;
	restore_fd();
	save_fd();
}
