/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst_to_file.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsiche <bsiche@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/24 13:28:02 by bsiche            #+#    #+#             */
/*   Updated: 2019/05/04 02:25:48 by bsiche           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh42.h"

int		rev_to_file(t_fcparse *opt, int fd)
{
	t_list		*tmp;

	tmp = ft_lstget(opt->max, g_tracking.mysh->hist->firstelement);
	while (tmp && (int)tmp->index > (opt->low - 1))
	{
		ft_putendl_fd(tmp->content, fd);
		tmp = tmp->prev;
	}
	return (0);
}

int		fc_to_file(t_fcparse *opt, int fd)
{
	t_list		*tmp;

	if (!opt || fd == -1)
		return (1);
	if (opt->r == 0)
	{
		tmp = ft_lstget(opt->low, g_tracking.mysh->hist->firstelement);
		while (tmp && (int)tmp->index < (opt->max + 1))
		{
			ft_putendl_fd(tmp->content, fd);
			tmp = tmp->next;
		}
		return (0);
	}
	else
		return (rev_to_file(opt, fd));
}

char	*fc_filename(void)
{
	char	*new;
	char	*nbr;

	new = ft_strdup("/tmp/fc");
	g_tracking.herenbr++;
	nbr = ft_itoa(g_tracking.herenbr);
	if (!nbr)
		return (NULL);
	new = ft_strjoinfree(new, nbr, 3);
	while (access(new, F_OK) != -1)
	{
		ft_strdel(&new);
		new = ft_strdup("/tmp/fc");
		g_tracking.herenbr++;
		nbr = ft_itoa(g_tracking.herenbr);
		if (!nbr)
			return (NULL);
		new = ft_strjoinfree(new, nbr, 3);
	}
	return (new);
}

int		create_fc_file(t_fcparse *opt)
{
	char	*file;
	int		fd;

	get_neg_offset(opt);
	if (!opt)
		return (-1);
	file = NULL;
	fd = 0;
	file = fc_filename();
	if (!file)
		return (-1);
	if ((fd = open(file, O_CREAT | O_RDWR, 0777)) == -1)
		ft_putendl_fd("Couldn't create file in /tmp", 2);
	if ((fc_to_file(opt, fd)) == 1)
		return (-1);
	close(fd);
	fc_edit(opt, file);
	unlink(file);
	ft_strdel(&file);
	return (0);
}
