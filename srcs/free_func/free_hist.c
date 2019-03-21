/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_hist.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdufer <hdufer@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/17 04:38:33 by bsiche            #+#    #+#             */
/*   Updated: 2019/03/21 18:32:41 by hdufer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh42.h"

void		free_hist(void)
{
	t_hist	*next;

	if (!g_tracking.mysh->hist)
		return ;
	while (g_tracking.mysh->hist->previous)
		g_tracking.mysh->hist = g_tracking.mysh->hist->previous;
	while (g_tracking.mysh->hist)
	{
		if (g_tracking.mysh->hist->line)
		{
			free(g_tracking.mysh->hist->line);
			g_tracking.mysh->hist->line = NULL;
		}
		next = g_tracking.mysh->hist->next;
		if (!g_tracking.mysh->hist || !g_tracking.mysh->hist->line)
			free(g_tracking.mysh->hist);
		g_tracking.mysh->hist = next;
	}
	g_tracking.mysh->hist = NULL;
}
