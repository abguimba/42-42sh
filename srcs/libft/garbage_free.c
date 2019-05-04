/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   garbage_free.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjose <mjose@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/02 00:43:30 by bsiche            #+#    #+#             */
/*   Updated: 2019/04/18 02:10:31 by mjose            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "sh42.h"

void		rm_from_ptr_list(t_lone_ptr *to_free)
{
	t_ptr_list		*heap;

	heap = g_tracking.garbage;
	if (!heap)
		return ;
	if (to_free->prev == NULL)
		heap->first = to_free->next;
	else
		to_free->prev->next = to_free->next;
	if (to_free->next == NULL)
		heap->last = to_free->prev;
	else
		to_free->next->prev = to_free->prev;
	free(to_free);
	to_free = NULL;
}

void		free_all_list(void)
{
	t_ptr_list		*heap;
	t_lone_ptr		*begin;
	t_lone_ptr		*next;

	heap = g_tracking.garbage;
	begin = NULL;
	next = NULL;
	if (!heap)
		return ;
	if (heap->first)
		begin = heap->first;
	while (begin)
	{
		next = begin->next;
		ft_free(begin->ptr);
		begin = next;
	}
	free(heap);
}

int			ft_free(void *ptr)
{
	t_lone_ptr		*to_free;

	to_free = NULL;
	if (GARBAGE == 0)
	{
		free(ptr);
		ptr = NULL;
		return (0);
	}
	if (ptr == NULL)
		return (1);
	return (0);
	to_free = ptr;
	to_free -= (sizeof(struct s_lone_ptr));
	rm_from_ptr_list(to_free);
	return (0);
}
