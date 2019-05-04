/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   garbage_malloc.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsiche <bsiche@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/01 08:58:23 by bsiche            #+#    #+#             */
/*   Updated: 2019/04/27 22:27:56 by bsiche           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "sh42.h"

void		add_to_ptr_list(t_lone_ptr *new_block)
{
	if (g_tracking.garbage->first == NULL)
	{
		g_tracking.garbage->first = new_block;
		g_tracking.garbage->last = new_block;
		new_block->next = NULL;
		new_block->prev = NULL;
	}
	else
	{
		new_block->prev = g_tracking.garbage->last;
		g_tracking.garbage->last->next = new_block;
		g_tracking.garbage->last = new_block;
	}
}

void		*garbage_alloc(size_t size)
{
	t_lone_ptr		*new_block;
	void			*ptr;

	size += sizeof(struct s_lone_ptr);
	if (!(new_block = malloc(size)))
		return (NULL);
	ptr = new_block;
	ptr += sizeof(struct s_lone_ptr);
	new_block->ptr = ptr;
	new_block->next = NULL;
	add_to_ptr_list(new_block);
	return (ptr);
}

void		*ft_malloc(size_t size)
{
	void		*ptr;

	ptr = NULL;
	if (GARBAGE == 1)
		return (garbage_alloc(size));
	if (!(ptr = malloc(size)))
	{
		ft_putstr_fd("FAILED TO ALLOCATE MEMORY FOR :", 2);
		ft_putendl_fd(PROGRAM, 2);
		exit(1);
	}
	ft_bzero(ptr, size);
	return (ptr);
}
