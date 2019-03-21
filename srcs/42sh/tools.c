/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abguimba <abguimba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/15 12:52:33 by alsomvil          #+#    #+#             */
/*   Updated: 2019/03/20 03:38:03 by abguimba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "sh42.h"

void	clean_tab_exec(char **tab_exec)
{
	int			i;

	i = 0;
	while (tab_exec[i] != '\0')
	{
		if (ft_strlen(tab_exec[i]) == 0)
		{
			ft_strdel(&tab_exec[i]);
			tab_exec[i] = NULL;
		}
		i++;
	}
}

int		spaces_line_check(char *line)
{
	int			i;

	i = 0;
	while (line[i] != '\0')
	{
		if (line[i] != ' ' && line[i] != '\n' && line[i] != '\t'
				&& line[i] != '\v' && line[i] != '\r')
			return (1);
		i++;
	}
	return (0);
}

char	**tab_dup(char **tob)
{
	int			i;
	char		**new;

	i = 0;
	while (tob[i])
		i++;
	if (!(new = malloc(sizeof(char*) * (i + 1))))
		return (NULL);
	i = 0;
	while (tob[i])
	{
		new[i] = ft_strdup(tob[i]);
		i++;
	}
	new[i] = NULL;
	return (new);
}
