/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjose <mjose@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/13 19:55:14 by bsiche            #+#    #+#             */
/*   Updated: 2019/04/16 03:05:26 by mjose            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstadd(t_list *listelement, t_list *newelement)
{
	newelement->index = (listelement->index + 1);
	newelement->prev = listelement;
	newelement->next = NULL;
	listelement->next = newelement;
	return (newelement);
}
