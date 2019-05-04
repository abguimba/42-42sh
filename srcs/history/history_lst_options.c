/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history_lst_options.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsiche <bsiche@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/16 15:14:07 by hdufer            #+#    #+#             */
/*   Updated: 2019/05/03 09:44:26 by bsiche           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh42.h"

int		verify_path_is_valid(char *path)
{
	int				fd;
	struct stat		path_stat;

	if (access(path, F_OK) == 0)
	{
		if (stat(path, &path_stat) == 0)
		{
			if ((S_ISREG(path_stat.st_mode) != 0))
			{
				fd = open(path, O_CREAT | O_RDWR, 00777);
				return (fd);
			}
			else
				return (-1);
		}
	}
	fd = open(path, O_CREAT | O_RDWR, 00777);
	return (fd);
}

char	*create_path_hist(void)
{
	char	*path;
	char	*user;

	path = ft_strdup("/Users/");
	user = getlogin();
	path = ft_strjoinfree(path, user, 1);
	path = ft_strjoinfree(path, "/.42hist", 1);
	return (path);
}

void	print_history(void)
{
	t_list	*tmp;
	char	*buf;

	tmp = ft_lstgetfirst(g_tracking.mysh->hist->firstelement);
	if (!tmp)
		return ;
	while (tmp)
	{
		buf = tmp->content;
		ft_putnbr(tmp->index + 1);
		ft_putstr(": ");
		ft_putendl(buf);
		tmp = tmp->next;
	}
	return ;
}

void	hist_file_to_lst(char *path, char *line, int fd)
{
	int				t;

	path = create_path_hist();
	fd = verify_path_is_valid(path);
	if (fd < 0)
		ft_putendl_fd("Error while opening/creating .42hist", 2);
	ft_free(path);
	if (g_tracking.mysh->hist == NULL)
		g_tracking.mysh->hist = lstcontainer_new();
	while ((t = get_next_line(fd, &line)) == 1 && line != NULL)
	{
		if (ft_strcmp(line, "\n") != 0 && ft_strlen(line) > 0
			&& ft_strlen(line) < 1024 && line[0] > 32)
			lstcontainer_add(g_tracking.mysh->hist, ft_strdup_nocar(line));
		if (line)
			ft_free(line);
		line = NULL;
	}
	ft_free(line);
	line = NULL;
	close(fd);
}
