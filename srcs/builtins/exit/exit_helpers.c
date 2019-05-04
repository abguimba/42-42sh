/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_helpers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abguimba <abguimba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/15 12:52:33 by mjose             #+#    #+#             */
/*   Updated: 2019/05/02 08:03:56 by abguimba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh42.h"

void		free_remains(void)
{
	ft_free(g_tracking.aliasloop);
	ft_free(g_tracking.pos);
	ft_free(g_tracking.cpaste->line);
	ft_free(g_tracking.cpaste);
	clean_tmp_local_env();
	ft_free(g_tracking.mysh);
}

void		free_and_null(void *ptr)
{
	if (ptr)
	{
		ft_free(ptr);
		ptr = NULL;
	}
}

int			ft_exit3(int exitcode, int mode)
{
	free_mysh();
	clean_up_leaks();
	clean_up_leaks();
	empty_hash_table();
	free_all_jobs();
	if (mode == 2)
		free_remains();
	if (GARBAGE == 1)
		free_all_list();
	exit(exitcode);
}
