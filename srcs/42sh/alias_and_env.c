/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   alias_and_env.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abguimba <abguimba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/07 02:06:25 by bsiche            #+#    #+#             */
/*   Updated: 2019/05/01 05:04:58 by abguimba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh42.h"

void			line_to_tab_cmds_h(int i, int j, char *line, char **taab)
{
	int		hold;
	int		l;

	while (line[i] != '\0')
	{
		hold = i;
		i = next_separator_quotes_check(line, i, 0);
		if (!(taab[j] = ft_malloc(sizeof(char) * i + 1)))
			return ;
		l = 0;
		while (hold < i)
		{
			taab[j][l] = line[hold];
			l++;
			hold++;
		}
		taab[j][l] = '\0';
		j++;
	}
	taab[j] = NULL;
}

char			**line_to_tab_cmds(char *line, int i, int count)
{
	char	**taab;

	i = 0;
	while (line[i])
	{
		i = next_separator_quotes_check(line, i, 0);
		count++;
		if (line[i])
			i++;
	}
	if (!(taab = ft_malloc(sizeof(char*) * (count + 2))))
		return (NULL);
	i = 0;
	line_to_tab_cmds_h(i, 0, line, taab);
	return (taab);
}

int				check_if_valid_quotes(char *str, int i, int j, int countequal)
{
	char		**taab;

	taab = line_to_tab_cmds(str, 0, 0);
	while (taab[i])
	{
		j = 0;
		while (taab[i][j] != '\0')
		{
			if (j > 0 && countequal == 0)
				break ;
			countequal = 0;
			while (taab[i][j] && is_spaces(taab[i], j, 2))
				j++;
			while (taab[i][j] && !is_spaces(taab[i], j, 1))
			{
				if (taab[i][j] == '=')
					countequal++;
				else if (taab[i][j] == '\"' || taab[i][j] == '\'')
					return (free_taab_and_return(taab, 0));
				j++;
			}
		}
		i++;
	}
	return (free_taab_and_return(taab, 1));
}
