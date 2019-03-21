/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstgetfirst.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsiche <bsiche@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/17 04:54:32 by bsiche            #+#    #+#             */
/*   Updated: 2018/08/13 04:42:39 by bsiche           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstgetfirst(t_list *lst)
{
	t_list	*tmp;

	tmp = lst;
	if (tmp)
	{
		while (lst->prev)
			lst = lst->prev;
		return (lst);
	}
	return (NULL);
}
