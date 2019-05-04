/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   garbage_init.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjose <mjose@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/01 08:41:47 by bsiche            #+#    #+#             */
/*   Updated: 2019/04/18 02:10:31 by mjose            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "sh42.h"

int		garbage_init(void)
{
	t_ptr_list		*heap;

	heap = NULL;
	if ((heap = malloc(sizeof(t_ptr_list))) == NULL)
	{
		g_tracking.garbage = NULL;
		ft_putstr_fd("FAILED TO ALLOCATE MEMORY FOR: ", 2);
		ft_putendl_fd(PROGRAM, 2);
		exit(1);
	}
	heap->first = NULL;
	heap->last = NULL;
	g_tracking.garbage = heap;
	return (1);
}
