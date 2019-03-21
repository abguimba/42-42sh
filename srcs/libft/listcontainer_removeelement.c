/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   listcontainer_removeelement.c                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cababou <cababou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/17 05:26:45 by cababou           #+#    #+#             */
/*   Updated: 2018/08/13 02:22:34 by cababou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	lstcontainer_remove(t_lstcontainer *liste, t_list *element, int freecnt)
{
	if (element->prev == NULL && element->next == NULL)
	{
		liste->firstelement = NULL;
		liste->lastelement = NULL;
	}
	if (element == liste->firstelement && element->next != NULL)
		liste->firstelement = element->next;
	if (element == liste->lastelement && element->prev != NULL)
		liste->lastelement = element->prev;
	ft_lstdelone(element, freecnt);
}
