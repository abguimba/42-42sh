/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_hist_ptr.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abguimba <abguimba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/19 02:58:40 by bsiche            #+#    #+#             */
/*   Updated: 2019/05/01 05:12:38 by abguimba         ###   ########.fr       */
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
	t_list		*tmp;
	int			i;

	tmp = NULL;
	i = 0;
	if (!g_tracking.mysh || !g_tracking.mysh->hist
	|| !g_tracking.mysh->hist->firstelement)
		return (NULL);
	tmp = g_tracking.mysh->hist->firstelement;
	tmp = ft_lstget(g_tracking.histindex - 1, tmp);
	if (!tmp)
		return (NULL);
	while (tmp)
	{
		if ((i = ft_strstr_ptr(tmp->content, needle) != -1))
		{
			return (tmp->content);
		}
		tmp = tmp->prev;
		if (g_tracking.histindex > 1)
			g_tracking.histindex--;
	}
	return (NULL);
}
