/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstget.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsiche <bsiche@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/27 02:44:18 by bsiche            #+#    #+#             */
/*   Updated: 2018/08/12 05:50:00 by bsiche           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstget(size_t index, t_list *anyelement)
{
	t_list	*el;

	el = ft_lstgetfirst(anyelement);
	while (el != NULL)
	{
		if (el->index == index)
			return (el);
		el = el->next;
	}
	return (NULL);
}
