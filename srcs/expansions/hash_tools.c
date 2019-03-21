/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hash_tools.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjose <mjose@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/12 05:27:55 by mjose             #+#    #+#             */
/*   Updated: 2019/02/13 06:05:06 by mjose            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expansions.h"

void	skip_found(char **str, char *value_var, char *to_srch)
{
	int		total_found;
	char	*tmp;
	int		i;

	total_found = ft_strlen(to_srch);
	i = 0;
	ft_strdel(str);
	tmp = value_var;
	while (total_found != i++)
		tmp++;
	*str = ft_strdup(tmp);
}
