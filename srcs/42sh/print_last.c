/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_last.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alsomvil <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/18 16:41:33 by alsomvil          #+#    #+#             */
/*   Updated: 2019/03/18 18:27:42 by alsomvil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh42.h"

void	print_last(t_last *list)
{
	while (list)
	{
		printf("CMD = %s TYPE = %d\n", list->name, list->type);
		list = list->next;
	}
}
