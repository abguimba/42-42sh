/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history_builtin_option.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abguimba <abguimba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/18 13:43:28 by hdufer            #+#    #+#             */
/*   Updated: 2019/03/20 06:11:03 by abguimba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh42.h"

void	history_builtin_s(void)
{
	int i;
	int j;
	int h;

	i = 2;
	j = 0;
	h = 0;
	if (!(g_tracking.g_tab_exec[i]))
		return ;
	else
		if (g_tracking.mysh->hist)
			g_tracking.mysh->hist = hist_delete_last(g_tracking.mysh->hist);
	g_tracking.mysh->hist = builtin_s_args(&g_tracking.g_tab_exec[i], g_tracking.mysh->hist);
}