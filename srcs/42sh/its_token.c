/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   its_token.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjose <mjose@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/19 04:18:28 by mjose             #+#    #+#             */
/*   Updated: 2019/04/18 02:10:31 by mjose            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh42.h"

int		its_fd_reddir(t_last *list)
{
	int		i;

	i = 0;
	while (list->name[i] && list->name[i] > 47 && list->name[i] < 58)
		i++;
	if (list->name[i] && list->name[i] == '>')
		return (1);
	return (0);
}

int		its_eper(t_last *list)
{
	int		i;

	i = 0;
	if (list && list->name[i]
			&& ft_strlen(list->name) == 1 && list->name[i] == '&')
		return (1);
	return (0);
}

int		its_indir(char *str)
{
	int		i;

	i = 0;
	while (str[i] && str[i] > 47 && str[i] < 58)
		i++;
	if (str[i] && str[i] == '<')
		return (1);
	return (0);
}

int		its_reddir(t_last *list)
{
	int		i;

	i = 0;
	if (list->name[i] && list->name[i] == '>')
		return (1);
	return (0);
}
