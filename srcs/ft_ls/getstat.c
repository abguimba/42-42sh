/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   getstat.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjose <mjose@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/14 18:47:53 by bsiche            #+#    #+#             */
/*   Updated: 2019/04/18 02:10:31 by mjose            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh42.h"

void	ft_special(t_ls *info, struct stat *tmp)
{
	char		*permission;

	permission = ft_usrmode(tmp->st_mode);
	if (permission[0] == 'l')
		info->symlink = ft_strdup("simlink");
	if (permission[0] == 'c' || permission[0] == 'b')
	{
		info->maj = major(tmp->st_rdev);
		info->min = minor(tmp->st_rdev);
	}
	ft_free(permission);
}

void	ft_stat2(t_ls *info, struct stat *tmp, time_t cur)
{
	info->permission = tmp->st_mode;
	info->size = tmp->st_size;
	if (((cur - tmp->st_mtime) > 15778476)
		|| ((tmp->st_mtime - cur) > 15778476))
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

	cur = 15778476;
	if ((tmp = ft_malloc(sizeof(struct stat) + 1)) == NULL)
		return (-1);
	if (lstat(path, tmp) == -1)
	{
		ft_free(tmp);
		return (-1);
	}
	u = checkoption(option, 'u');
	if (u == 0)
		info->time = tmp->st_mtime;
	if (u == 1)
		info->time = tmp->st_atime;
	ft_stat2(info, tmp, cur);
	ft_special(info, tmp);
	ft_free(tmp);
	return (0);
}
