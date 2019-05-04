/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   paste.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjose <mjose@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/10 19:41:54 by bsiche            #+#    #+#             */
/*   Updated: 2019/05/04 08:10:30 by mjose            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh42.h"

void	begin_paste(void)
{
	char	*tmp;

	if (!g_tracking.cpaste || !g_tracking.cpaste->line
		|| ft_strlen(g_tracking.cpaste->line) < 1)
		return ;
	tmp = ft_strdup(g_tracking.cpaste->line);
	if (g_tracking.cpaste->line)
		add_to_str(ft_strdup(tmp));
	ft_strdel(&tmp);
}
