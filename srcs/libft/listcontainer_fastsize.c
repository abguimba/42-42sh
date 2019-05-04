/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   listcontainer_fastsize.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjose <mjose@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/17 05:29:49 by bsiche            #+#    #+#             */
/*   Updated: 2019/04/16 03:06:39 by mjose            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		lstcontainer_fastsize(t_lstcontainer *container)
{
	return (container->lastelement->index + 1);
}
