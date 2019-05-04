/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sanitize_path_helper.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjose <mjose@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/04 01:54:20 by mjose             #+#    #+#             */
/*   Updated: 2019/05/04 07:28:33 by mjose            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh42.h"

char	*check_multi_slash(char *path)
{
	char	*new_path;
	int		i;

	i = 0;
	if (!path)
		return (NULL);
	while (path[i] && path[i] == '/')
		i++;
	new_path = ft_strdup(path + (i - 1));
	ft_strdel(&path);
	return (new_path);
}

int		is_dir(char *path)
{
	struct stat		path_stat;

	if (!path)
		return (1);
	if (access(path, F_OK) == 0)
	{
		if (stat(path, &path_stat) == 0)
			if ((S_ISDIR(path_stat.st_mode) != 0))
				return (1);
	}
	return (0);
}
