/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   listcontainer_reindex.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjose <mjose@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/17 05:29:49 by bsiche            #+#    #+#             */
/*   Updated: 2019/04/16 03:07:04 by mjose            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	lstcontainer_reindex(t_lstcontainer *container)
{
	t_list	*element;
	int		i;

	element = container->firstelement;
	i = 0;
	while (element)
	{
		element->index = i;
		element = element->next;
		i++;
	}
}
