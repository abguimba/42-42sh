/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mergesort.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsiche <bsiche@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/15 20:13:03 by bsiche            #+#    #+#             */
/*   Updated: 2018/12/18 20:21:06 by bsiche           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh42.h"

t_list	*cmpsize(t_list *start, t_list *mid)
{
	t_ls			*tmp;
	t_ls			*tmp2;

	if (mid == NULL)
		return (start);
	else if (start == NULL)
		return (mid);
	tmp = start->content;
	tmp2 = mid->content;
	if (tmp->size > tmp2->size)
	{
		start->next = cmpsize(start->next, mid);
		start->next->prev = start;
		start->prev = NULL;
		return (start);
	}
	else
	{
		mid->next = cmpsize(start, mid->next);
		mid->next->prev = mid;
		mid->prev = NULL;
		return (mid);
	}
}

t_list	*cmpname(t_list *start, t_list *mid)
{
	t_ls			*tmp;
	t_ls			*tmp2;

	if (mid == NULL)
		return (start);
	else if (start == NULL)
		return (mid);
	tmp = start->content;
	tmp2 = mid->content;
	if (ft_strcmp(tmp->name, tmp2->name) < 0)
	{
		start->next = cmpname(start->next, mid);
		start->next->prev = start;
		start->prev = NULL;
		return (start);
	}
	else
	{
		mid->next = cmpname(start, mid->next);
		mid->next->prev = mid;
		mid->prev = NULL;
		return (mid);
	}
}

t_list	*ft_getmid(t_list *start)
{
	t_list	*tmp;
	t_list	*tmp2;
	t_list	*mid;

	tmp = start;
	tmp2 = start;
	while (tmp2->next && tmp2->next->next)
	{
		tmp2 = tmp2->next->next;
		tmp = tmp->next;
	}
	mid = tmp->next;
	tmp->next = NULL;
	return (mid);
}

t_list	*ft_mergesort(t_list *start, int i)
{
	t_list		*mid;

	if (!start || !start->next)
		return (start);
	mid = ft_getmid(start);
	start = ft_mergesort(start, i);
	mid = ft_mergesort(mid, i);
	if (i == 0)
		return (cmpname(start, mid));
	if (i == 1)
		return (cmpsize(start, mid));
	if (i == 2)
		return (cmptime(start, mid));
	else
		return (cmptimename(start, mid));
}
