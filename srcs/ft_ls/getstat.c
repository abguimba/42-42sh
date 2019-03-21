/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   getstat.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsiche <bsiche@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/14 18:47:53 by bsiche            #+#    #+#             */
/*   Updated: 2019/03/06 01:37:14 by bsiche           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh42.h"

void	ft_special(t_ls *info, struct stat *tmp, char *str)
{
	char		*permission;
	char		*symlink;
	char		*fleche;

	permission = ft_usrmode(tmp->st_mode);
	if (permission[0] == 'l')
	{
		symlink = ft_strnew(1025);
		readlink(str, symlink, 1025);
		fleche = ft_strdup("-> ");
		symlink = ft_strjoinfree(fleche, symlink, 3);
		symlink = ft_strjoinfree(symlink, "\0", 1);
		info->symlink = symlink;
	}
	if (permission[0] == 'c' || permission[0] == 'b')
	{
		info->maj = major(tmp->st_rdev);
		info->min = minor(tmp->st_rdev);
	}
	free(permission);
}

void	ft_stat2(t_ls *info, struct stat *tmp, time_t cur)
{
	info->permission = tmp->st_mode;
	info->size = tmp->st_size;
	if (((cur - tmp->st_mtime) > 15778476) ||
		((tmp->st_mtime - cur) > 15778476))
		info->timeswitch = 1;
	info->hardlink = tmp->st_nlink;
	info->block = tmp->st_blocks;
	info->usrname = tmp->st_uid;
	info->group = tmp->st_gid;
	info->symlink = NULL;
	info->acl = ' ';
	info->maj = 0;
	info->min = 0;
	info->color = 0;
	info->strpad = NULL;
}

int		ft_stat(char *path, t_ls *info, char *option)
{
	struct stat		*tmp;
	time_t			cur;
	int				u;

	cur = time(NULL);
	if ((tmp = malloc(sizeof(struct stat) + 1)) == NULL)
		return (-1);
	if (lstat(path, tmp) == -1)
	{
		free(tmp);
		return (-1);
	}
	u = checkoption(option, 'u');
	if (u == 0)
		info->time = tmp->st_mtime;
	if (u == 1)
		info->time = tmp->st_atime;
	ft_stat2(info, tmp, cur);
	ft_special(info, tmp, path);
	free(tmp);
	return (0);
}
