/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstdel.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjose <mjose@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/11 17:10:41 by bsiche            #+#    #+#             */
/*   Updated: 2019/04/16 03:05:35 by mjose            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstdel(t_list *lst, int free_content)
{
	t_list	*element;
	t_list	*next;

	if (lst == NULL)
		return ;
	element = ft_lstgetfirst(lst);
	while (element)
	{
		if (element->content && free_content)
			ft_free(element->content);
		next = element->next;
		ft_free(element);
		element = next;
	}
}
