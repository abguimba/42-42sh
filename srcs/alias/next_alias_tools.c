/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   next_alias_tools.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abguimba <abguimba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/17 23:37:20 by bsiche            #+#    #+#             */
/*   Updated: 2019/04/30 22:26:34 by abguimba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh42.h"

int			free_hold_and_i(int i, char *hold)
{
	i++;
	ft_strdel(&hold);
	return (i);
}

char		*taab_to_line(char **taab, char *hold)
{
	int		i;
	char	*new;

	new = NULL;
	i = 0;
	while (taab[i])
	{
		if (new != NULL)
			new = ft_strjoinfree(new, taab[i], 1);
		else
			new = ft_strdup(taab[i]);
		i++;
	}
	free_tab(taab);
	ft_strdel(&hold);
	return (new);
}

char		**line_to_taab(char *line, int i, int j)
{
	int		count;
	char	**taab;

	i = 0;
	count = 0;
	while (line[i])
	{
		i = next_separator(line, i);
		count++;
		if (line[i])
		{
			i++;
			if (line[i] == '\0')
				count++;
		}
	}
	if (!(taab = ft_malloc(sizeof(char*) * (count + 1))))
		return (NULL);
	i = 0;
	j = 0;
	alias_swapper_helper(i, j, line, taab);
	ft_strdel(&line);
	return (taab);
}

int			get_last_char_helper(char *str, char *memory, int i, int j)
{
	while (i > 0 && j > 0 && str[i] == memory[j])
	{
		i--;
		j--;
	}
	return (i + 1);
}

int			get_last_char_alias(char *str, char *memory, int nbsave, int j)
{
	int		i;
	int		saver;

	saver = nbsave;
	i = 0;
	while (nbsave > 0)
	{
		while (is_spaces(str, i, 1))
			i++;
		while (str[i] && !is_spaces(str, i, 2))
			i++;
		nbsave--;
	}
	while (saver > 0)
	{
		while (is_spaces(memory, j, 1))
			j++;
		while (memory[j] && !is_spaces(memory, j, 2))
			j++;
		saver--;
	}
	return (get_last_char_helper(str, memory, i - 1, j - 1));
}
