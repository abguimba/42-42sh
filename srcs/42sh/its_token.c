/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   its_token.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alsomvil <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/19 04:18:28 by alsomvil          #+#    #+#             */
/*   Updated: 2019/03/18 18:20:53 by alsomvil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/sh42.h"

int		its_reddir_to_fd(t_last *list)
{
	int		i;

	i = 0;
	while (list->name[i] && list->name[i] > 47 && list->name[i] < 58)
		i++;
	if (list->name[i] && list->name[i] == '>'
			&& list->name[i + 1] && list->name[i + 1] == '&')
		return (1);
	return (0);
}

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

int		its_indir(t_last *list)
{
	int		i;

	i = 0;
	while (list->name[i] && list->name[i] > 47 && list->name[i] < 58)
		i++;
	if (list->name[i] && list->name[i] == '<')
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
