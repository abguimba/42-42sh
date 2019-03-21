/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   timesort.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsiche <bsiche@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/16 23:51:31 by bsiche            #+#    #+#             */
/*   Updated: 2018/12/18 20:21:06 by bsiche           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh42.h"

t_list	*cmptime(t_list *start, t_list *mid)
{
	t_ls			*tmp;
	t_ls			*tmp2;

	if (mid == NULL)
		return (start);
	else if (start == NULL)
		return (mid);
	tmp = start->content;
	tmp2 = mid->content;
	if (tmp->time < tmp2->time)
	{
		start->next = cmptime(start->next, mid);
		start->next->prev = start;
		start->prev = NULL;
		return (start);
	}
	else
	{
		mid->next = cmptime(start, mid->next);
		mid->next->prev = mid;
		mid->prev = NULL;
		return (mid);
	}
}

t_list	*cmptimename(t_list *start, t_list *mid)
{
	t_ls			*tmp;
	t_ls			*tmp2;

	if (mid == NULL)
		return (start);
	else if (start == NULL)
		return (mid);
	tmp = start->content;
	tmp2 = mid->content;
	if ((tmp->name < tmp2->name) && (tmp->time == tmp2->time))
	{
		start->next = cmptimename(start->next, mid);
		start->next->prev = start;
		start->prev = NULL;
		return (start);
	}
	else
	{
		mid->next = cmptimename(start, mid->next);
		mid->next->prev = mid;
		mid->prev = NULL;
		return (mid);
	}
}
