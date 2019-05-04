/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsplitlst.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsiche <bsiche@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/29 23:37:38 by bsiche            #+#    #+#             */
/*   Updated: 2019/04/29 03:20:32 by bsiche           ###   ########.fr       */
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
			ft_strdel(&tab[i]);
			i++;
		}
	}
	ft_free(tab);
	tab = NULL;
}

void			free_two_tabs(char **tab1, char **tab2)
{
	free_tab(tab1);
	free_tab(tab2);
}

void			ft_freelstsplit(t_lstcontainer *list)
{
	t_list		*tmp;

	tmp = list->firstelement;
	while (tmp)
	{
		ft_free(tmp->content);
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
		ft_free(list);
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
