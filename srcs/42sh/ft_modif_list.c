/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_modif_list.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alsomvil <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/31 01:46:30 by alsomvil          #+#    #+#             */
/*   Updated: 2019/02/20 17:40:17 by alsomvil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_last	*create_new_list(void)
{
	t_last	*list;

	list = malloc(sizeof(t_last));
	list->name = NULL;
	list->next = NULL;
	list->prev = NULL;
	return (list);
}
