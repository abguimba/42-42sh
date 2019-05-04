/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history_lst.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjose <mjose@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/08 15:00:21 by hdufer            #+#    #+#             */
/*   Updated: 2019/05/04 08:17:08 by mjose            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh42.h"

void		hist_to_file(int fd)
{
	t_list	*hist;
	int		i;

	if (!g_tracking.mysh || !g_tracking.mysh->hist)
		return ;
	hist = ft_lstgetfirst(g_tracking.mysh->hist->firstelement);
	if (!hist)
		return ;
	while (hist)
	{
		if (hist->content != NULL)
		{
			i = ft_strlen(hist->content);
			if (i > 0 && i < 1024 && ft_strcmp(hist->content, "\n") != 0)
				ft_putendl_fd(hist->content, fd);
		}
		hist = hist->next;
	}
}

void		hist_save_file(void)
{
	int				fd;
	char			*path;

	path = create_path_hist();
	fd = verify_path_is_valid(path);
	if (fd < 0)
	{
		ft_strdel(&path);
		return (ft_putendl_fd("Error while opening/creating .42hist", 2));
	}
	hist_to_file(fd);
	ft_strdel(&path);
	close(fd);
	return ;
}
