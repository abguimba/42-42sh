/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_job_control.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjose <mjose@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/15 12:52:33 by mjose             #+#    #+#             */
/*   Updated: 2019/04/18 02:10:31 by mjose            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh42.h"

int					rellocate_cmd(t_last *p, int mode)
{
	if (mode == -1)
	{
		while (p && ft_strcmp(p->name, "||") && ft_strcmp(p->name, ";"))
		{
			p->check = 1;
			p = p->next;
		}
		if (!p)
			return (-1);
		else
			p->check = 1;
	}
	else if (mode == 0)
	{
		while (p && ft_strcmp(p->name, "&&") && ft_strcmp(p->name, ";"))
		{
			p->check = 1;
			p = p->next;
		}
		if (!p)
			return (-1);
		else
			p->check = 1;
	}
	return (0);
}
