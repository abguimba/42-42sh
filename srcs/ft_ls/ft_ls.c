/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjose <mjose@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/14 17:41:15 by bsiche            #+#    #+#             */
/*   Updated: 2019/04/18 02:10:31 by mjose            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh42.h"

void			ft_handlelink(t_list *list, char *dossier, int *flag)
{
	t_ls	*info;
	char	*perm;
	int		i;

	if (list != NULL)
	{
		info = list->content;
		perm = ft_usrmode(info->permission);
		i = ft_strlen(dossier) - 1;
		if (perm[0] == 'l' && dossier[i] != '/')
		{
			info->issimple = 1;
			*flag = 1;
		}
		ft_free(perm);
	}
}

void			get_and_sort(t_lstcontainer *mainliste, char *option)
{
	ft_sort(mainliste->firstelement, option);
	ft_strinfo(mainliste->firstelement);
}

t_lstcontainer	*ft_folderlist(t_lstcontainer *mainliste, DIR *dir,
char *dossier, char *option)
{
	t_lstcontainer *new_mainliste;

	free_all(mainliste, NULL);
	new_mainliste = lstcontainer_new();
	new_mainliste = makelist(new_mainliste, dir, dossier, option);
	return (new_mainliste);
}

t_lstcontainer	*ft_ls(char *name, char *option)
{
	t_lstcontainer		*mainliste;
	DIR					*dir;
	int					flag;
	char				*dossier;

	flag = 0;
	dossier = ft_strdup(name);
	dir = chkdir(dossier, &flag);
	mainliste = simpleinfo(dossier, option);
	if (ft_edgecase(dossier) == 1)
		return (free_all(mainliste, dossier));
	if (dir == NULL && flag == 0)
		return (free_all(mainliste, dossier));
	if (flag != 1 && checkoption(option, 'd') != 1)
		mainliste = ft_folderlist(mainliste, dir, dossier, option);
	if (dir != NULL)
		closedir(dir);
	if (mainliste->firstelement == NULL)
		return (free_all(mainliste, dossier));
	if (needstat(option) == 1)
		get_and_sort(mainliste, option);
	ft_free(dossier);
	return (mainliste);
}
