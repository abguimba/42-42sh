/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_modif_list.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abe <abe@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/31 01:46:30 by mjose             #+#    #+#             */
/*   Updated: 2019/04/30 15:21:19 by abe              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh42.h"

t_last	*create_new_list(void)
{
	t_last	*list;

	list = ft_malloc(sizeof(t_last));
	list->name = NULL;
	list->next = NULL;
	list->prev = NULL;
	list->type = -1;
	return (list);
}
