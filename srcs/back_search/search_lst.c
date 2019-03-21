/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   search_lst.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abguimba <abguimba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/24 00:28:43 by bsiche            #+#    #+#             */
/*   Updated: 2019/03/20 06:11:03 by abguimba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh42.h"

int				ft_strstr_ptr(const char *haystack, const char *needle)
{
	size_t		i;
	size_t		j;

	i = 0;
	j = 0;
	if (!haystack || !needle)
		return (-1);
	if (ft_strlen(needle) == 0)
		return (-1);
	while (haystack[i])
	{
		while (needle[j] == haystack[i])
		{
			i++;
			j++;
			if (needle[j] == '\0')
				return ((i - ft_strlen(needle)));
		}
		i = i - j;
		j = 0;
		i++;
	}
	return (-1);
}

char			*get_hist_ptr(char *needle)
{
	t_hist		*tmp;
	int			i;

	tmp = NULL;
	i = 0;
	tmp = get_hist_nbr(g_tracking.histindex - 1);
	if (!tmp)
		return (NULL);
	while (tmp)
	{
		if ((i = ft_strstr_ptr(tmp->line, needle) != -1))
		{
			return (tmp->line);
		}
		tmp = tmp->previous;
		if (g_tracking.histindex > 1)
			g_tracking.histindex--;
	}
	return (NULL);
}
