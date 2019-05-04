/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_keep_char.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abguimba <abguimba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/13 03:22:10 by mjose             #+#    #+#             */
/*   Updated: 2019/05/01 05:18:40 by abguimba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int				ft_isspace(char c)
{
	if (c == '\t' || c == ' ' || (c == '\n' && c != '\0'))
		return (1);
	return (0);
}

void			split_loop(char *str, t_lstcontainer *list, int i, char *blank)
{
	while (str[i] != '\0')
	{
		blank = ft_strnew(0);
		while (ft_isspace(str[i]) == 1)
		{
			blank = ft_strjoinchar(blank, str[i], 1);
			i++;
		}
		lstcontainer_add(list, ft_strdup(blank));
		ft_strdel(&blank);
		blank = ft_strnew(0);
		if (str[i] != '\0')
		{
			while (str[i] && ft_isspace(str[i]) == 0)
			{
				blank = ft_strjoinchar(blank, str[i], 1);
				i++;
			}
			lstcontainer_add(list, ft_strdup(blank));
			ft_strdel(&blank);
		}
	}
	if (blank)
		ft_strdel(&blank);
}

t_lstcontainer	*ft_split_with_char(char *str)
{
	t_lstcontainer	*list;
	int				j;

	j = 0;
	if (!str)
		return (NULL);
	list = lstcontainer_new();
	if (!list)
		return (NULL);
	split_loop(str, list, 0, NULL);
	return (list);
}
