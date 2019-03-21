/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   listcontainer_addelement.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsiche <bsiche@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/13 01:52:15 by bsiche            #+#    #+#             */
/*   Updated: 2018/08/13 01:52:16 by bsiche           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	lstcontainer_add(t_lstcontainer *container, void *content)
{
	if (container == NULL)
		container = lstcontainer_new();
	if (container->firstelement == NULL)
	{
		container->firstelement = ft_lstnew(content);
		container->lastelement = container->firstelement;
	}
	else
		container->lastelement = ft_lstadd(container->lastelement,
			ft_lstnew(content));
}
