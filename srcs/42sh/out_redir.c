/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   out_redir.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjose <mjose@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/15 18:52:18 by mjose             #+#    #+#             */
/*   Updated: 2019/05/02 23:34:49 by mjose            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh42.h"

int		search_in(char *str, int mode)
{
	int		fd;
	int		i;

	fd = mode;
	i = 0;
	while (str[i] >= '0' && str[i] <= '9')
		i++;
	if (i == 0)
		return (fd);
	else if (i < 2)
		fd = str[0] - '0';
	else
	{
		ft_putstr_fd("42sh: ", 2);
		ft_putstr_fd(str, 2);
		ft_putendl_fd(": bad file descriptor", 2);
	}
	return (fd);
}

int		file_exist(char **tab_redir, int fd_in, int fd_out, int i)
{
	if (fd_out == -1)
	{
		ft_putstr_fd("42sh: no such file or directory: ", 2);
		ft_putendl_fd(tab_redir[i], 2);
		return (-1);
	}
	else
	{
		dup2(fd_out, fd_in);
		close(fd_out);
	}
	return (0);
}

int		out_redir(char **tab_reddir, int i)
{
	int		fd_in;
	int		fd_out;

	fd_in = search_in(tab_reddir[i], 0);
	i++;
	if (ft_strlen(tab_reddir[i]) == 1 && tab_reddir[i][0] >= '0'
			&& tab_reddir[i][0] <= '9')
	{
		fd_out = tab_reddir[i][0] - 48;
		if (write(fd_out, "0", 0) == -1)
		{
			ft_putstr_fd("42sh: ", 2);
			ft_putnbr_fd(fd_out, 2);
			ft_putendl_fd(": bad file descriptor", 2);
			return (-1);
		}
	}
	else if (!ft_strcmp(tab_reddir[i], "-"))
		fd_out = open("/dev/null", O_RDONLY);
	else
		fd_out = open(tab_reddir[i], O_RDONLY);
	return (file_exist(tab_reddir, fd_in, fd_out, i));
}
