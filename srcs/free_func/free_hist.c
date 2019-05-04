/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_hist.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsiche <bsiche@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/17 04:38:33 by bsiche            #+#    #+#             */
/*   Updated: 2019/05/02 10:33:54 by bsiche           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh42.h"

void		free_hist(void)
{
	t_list	*hist;

	if (!g_tracking.mysh->hist)
		return ;
	hist = ft_lstgetfirst(g_tracking.mysh->hist->firstelement);
	if (!hist)
	{
		ft_free(g_tracking.mysh->hist);
		return ;
	}
	ft_lstdel(hist, 1);
	ft_free(g_tracking.mysh->hist);
	g_tracking.mysh->hist = NULL;
	return ;
}
