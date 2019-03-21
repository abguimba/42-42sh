/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsplitlst.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsiche <bsiche@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/29 23:37:38 by bsiche            #+#    #+#             */
/*   Updated: 2018/12/18 23:55:37 by bsiche           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void			free_tab(char **tab)
{
	int i;

	i = 0;
	if (tab != NULL)
	{
		while (tab[i])
		{
			free(tab[i]);
			i++;
		}
	}
	free(tab);
}

void			ft_freelstsplit(t_lstcontainer *list)
{
	t_list		*tmp;

	tmp = list->firstelement;
	while (tmp)
	{
		free(tmp->content);
		tmp = tmp->next;
	}
}

void			ft_freesplitlist(t_lstcontainer *list)
{
	if (list != NULL)
	{
		ft_freelstsplit(list);
		if (list->firstelement != NULL)
			ft_lstdel(list->firstelement, 0);
		free(list);
	}
}

t_lstcontainer	*ft_strsplitlst(char *str, char c)
{
	t_lstcontainer	*new;
	int				i;
	char			**tab;

	new = NULL;
	tab = ft_strsplit(str, c);
	i = 0;
	if (tab[i])
		new = lstcontainer_new();
	while (tab[i])
	{
		new->add(new, ft_strdup(tab[i]));
		i++;
	}
	free_tab(tab);
	return (new);
}
