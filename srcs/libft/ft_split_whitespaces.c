/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_whitespaces.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alsomvil <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/13 03:22:10 by alsomvil          #+#    #+#             */
/*   Updated: 2018/12/04 17:15:13 by alsomvil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int		ft_nbletter(char *str, int i)
{
	int nbletter;

	nbletter = 0;
	while ((str[i] != '\t' && str[i] != ' ' && str[i] != '\n')
			&& str[i] != '\0')
	{
		i++;
		nbletter++;
	}
	return (nbletter);
}

static int		ft_nbword(char *str)
{
	int		i;
	int		word;

	i = 0;
	word = 0;
	while (str[i] != '\0')
	{
		while ((str[i] == '\t' || str[i] == ' ' || str[i] == '\n')
				&& str[i] != '\0')
		{
			i++;
			if (str[i] == '\0')
				word--;
		}
		word++;
		while ((str[i] != '\t' && str[i] != ' ' && str[i] != '\n')
				&& str[i] != '\0')
			i++;
	}
	return (word);
}

char			**ft_split_whitespaces(char *str)
{
	int		i;
	int		j;
	int		k;
	char	**tab;

	i = 0;
	j = 0;
	tab = malloc(sizeof(char*) * (ft_nbword(str) + 1));
	while (str[i] != '\0')
	{
		while ((str[i] == '\t' || str[i] == ' ' || str[i] == '\n')
				&& str[i] != '\0')
			i++;
		if (str[i] != '\0')
		{
			k = 0;
			tab[j] = malloc(sizeof(char) * (ft_nbletter(str, i) + 1));
			while ((str[i] != '\t' && str[i] != ' ' && str[i] != '\n')
					&& str[i] != '\0')
				tab[j][k++] = str[i++];
			tab[j++][k] = '\0';
		}
	}
	tab[j] = 0;
	return (tab);
}
