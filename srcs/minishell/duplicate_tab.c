/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   duplicate_tab.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alsomvil <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/21 04:20:10 by alsomvil          #+#    #+#             */
/*   Updated: 2018/12/04 16:41:31 by alsomvil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	**duplicate_tab_two(char ***tab, int j)
{
	char	**temp;
	int		i;
	int		k;

	i = 0;
	k = 0;
	temp = NULL;
	while ((*tab)[i])
		i++;
	temp = malloc(sizeof(char *) * (i));
	i = 0;
	while ((*tab)[i])
	{
		if (i == j)
			i++;
		else
		{
			temp[k] = ft_strdup((*tab)[i]);
			i++;
			k++;
		}
	}
	temp[k] = NULL;
	freetab(*tab);
	return (temp);
}

char	**duplicate_tab(char ***tab)
{
	char	**temp;
	int		i;

	i = 0;
	temp = NULL;
	while ((*tab)[i])
		i++;
	temp = malloc(sizeof(char *) * (i + 3));
	i = 0;
	while ((*tab)[i])
	{
		temp[i] = ft_strdup((*tab)[i]);
		i++;
	}
	temp[i] = NULL;
	temp[i + 1] = NULL;
	freetab(*tab);
	return (temp);
}

char	**duplicate_env(char **tab)
{
	char	**temp;
	int		i;

	i = 0;
	temp = NULL;
	while (tab[i])
		i++;
	temp = ft_memalloc(sizeof(char *) * (i + 1));
	i = 0;
	while (tab[i])
	{
		temp[i] = ft_strdup(tab[i]);
		i++;
	}
	temp[i] = NULL;
	return (temp);
}
