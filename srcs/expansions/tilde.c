/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tilde.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjose <mjose@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/01 00:31:23 by mjose             #+#    #+#             */
/*   Updated: 2019/02/01 00:43:20 by mjose            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expansions.h"

int		is_path_tilde(char *to_transf)
{
	int		i;

	i = 0;
	while (to_transf[i])
	{
		if (to_transf[i] == '~' && i && to_transf[i - 1] == '/'
				&& !to_transf[i + 1])
			return (1);
		else if (to_transf[i] == '~' && i && to_transf[i - 1] == '/'
				&& to_transf[i + 1] == '/')
			return (1);
		i++;
	}
	return (0);
}
