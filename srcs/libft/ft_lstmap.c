/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsiche <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/17 04:55:20 by bsiche            #+#    #+#             */
/*   Updated: 2018/02/17 04:55:22 by bsiche           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list		*ft_lstmap(t_list *lst, t_list *(*f)(t_list *elem))
{
	t_list	*buf;

	if (lst == NULL)
		return (NULL);
	buf = (t_list *)malloc(sizeof(t_list));
	buf = f(lst);
	if (lst->next != NULL)
		buf->next = ft_lstmap(lst->next, *f);
	return (buf);
}
