/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   listcontainer_size.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjose <mjose@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/17 05:29:49 by bsiche            #+#    #+#             */
/*   Updated: 2019/04/16 03:07:23 by mjose            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		lstcontainer_size(t_lstcontainer *list_container)
{
	t_list	*lst;
	int		size;

	size = 0;
	if (list_container == NULL)
		return (-1);
	lst = list_container->firstelement;
	while (lst)
	{
		lst = lst->next;
		size++;
	}
	return (size);
}
