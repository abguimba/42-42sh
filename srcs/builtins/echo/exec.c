/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjose <mjose@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/01 07:59:43 by mjose             #+#    #+#             */
/*   Updated: 2019/04/18 02:10:31 by mjose            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh42.h"

void	exec_echo(void)
{
	char	**tab_arg;
	int		i;

	i = 0;
	tab_arg = g_tracking.g_tab_exec + 1;
	while (*tab_arg)
	{
		if (i > 0)
			ft_putchar(' ');
		ft_putstr(*tab_arg);
		tab_arg++;
		i++;
	}
	ft_putchar('\n');
}

int		check_and_exec_echo(void)
{
	char	**tab_arg;

	if (write(1, "\0", 0) == -1)
		return (1);
	tab_arg = g_tracking.g_tab_exec + 1;
	if (!tab_arg)
		ft_putchar('\n');
	else
		exec_echo();
	return (0);
}
