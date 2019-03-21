/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   alias_file.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abguimba <abguimba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/15 22:29:58 by bsiche            #+#    #+#             */
/*   Updated: 2019/03/20 07:17:27 by abguimba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh42.h"

char	*create_path(void)
{
	char	*path;
	char	*user;

	path = ft_strdup("/Users/");
	user = getlogin();
	path = ft_strjoinfree(path, user, 1);
	path = ft_strjoinfree(path, "/42shrc", 1);
	return (path);
}

int		init_alias(void)
{
	int				fd;
	t_lstcontainer	*alias_lst;
	char			*alias;
	char			*path;

	alias_lst = NULL;
	path = create_path();
	fd = open(path, O_RDWR | O_CREAT, 0777);
	free(path);
	if (fd == -1)
	{
		ft_putstr_fd("Failed to create or load ~/42shrc, ", 2);
		ft_putstr_fd("please check your read/write permissions", 2);
		return (-1);
	}
	alias_lst = lstcontainer_new();
	while (get_next_line(fd, &alias) != 0)
	{
		lstcontainer_add(alias_lst, parse_alias(alias));
		free(alias);
	}
	close(fd);
	g_tracking.mysh->alias_lst = alias_lst;
	return (0);
}
