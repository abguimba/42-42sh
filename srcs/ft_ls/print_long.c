/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_long.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsiche <bsiche@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/18 16:24:14 by bsiche            #+#    #+#             */
/*   Updated: 2018/05/23 19:47:27 by bsiche           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void	reverselist(t_list *liste)
{
	t_list	*buf;
	t_list	*tmp;
	int		i;

	buf = ft_lstgetfirst(liste);
	tmp = NULL;
	i = ft_lstgetlast(liste)->index;
	while (buf != NULL)
	{
		tmp = buf->prev;
		buf->prev = buf->next;
		buf->next = tmp;
		buf->index = i;
		i--;
		buf = buf->prev;
	}
	if (tmp != NULL)
		liste = tmp->prev;
}

char	**gettab(t_ls *tmp)
{
	char **tab;

	tab = malloc(sizeof(char *) * 9);
	tab[0] = tmp->strpermission;
	tab[1] = tmp->strlink;
	tab[2] = tmp->strusrname;
	tab[3] = tmp->strgroup;
	if (tmp->strpermission[0] == 'b' || tmp->strpermission[0] == 'c')
		tab[4] = tmp->strmaj;
	else
		tab[4] = tmp->strsize;
	tab[5] = tmp->strtime;
	tab[6] = tmp->name;
	tab[7] = tmp->symlink;
	tab[8] = NULL;
	return (tab);
}

void	ft_printtab(t_ls *tmp, char **tab, int g)
{
	int i;

	i = 0;
	while (tab[i] != NULL)
	{
		if (i == 6 && g == 1)
			ft_putcolor(tmp->color);
		ft_putstr(tab[i]);
		if (g == 1)
			ft_putcolor(12);
		if (tab[i + 1] != NULL)
			ft_putstr(" ");
		i++;
	}
}

int		ft_printl(t_list *liste, int g)
{
	t_ls	*tmp;
	char	**tab;
	t_list	*buf;

	if (liste == NULL)
		return (0);
	buf = ft_lstgetfirst(liste);
	if (g == 1)
		color(liste);
	while (buf != NULL)
	{
		tmp = buf->content;
		tab = gettab(tmp);
		ft_printtab(tmp, tab, g);
		ft_putchar('\n');
		free(tab);
		buf = buf->next;
	}
	return (0);
}
