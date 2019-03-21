/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_two.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alsomvil <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/13 15:58:29 by alsomvil          #+#    #+#             */
/*   Updated: 2018/12/04 16:41:52 by alsomvil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	forfree(char **tab)
{
	int		i;

	i = 0;
	if (tab[0])
	{
		while (tab[i])
			free(tab[i++]);
	}
	free(tab);
}

int		verif_char(char *line)
{
	int		i;

	i = 0;
	while (line[i] && (line[i] == ' ' || line[i] == '\t'))
		i++;
	if (line[i] == '\0')
		return (0);
	return (1);
}
