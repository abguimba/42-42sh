/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_create_fich.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abguimba <abguimba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/18 16:42:28 by alsomvil          #+#    #+#             */
/*   Updated: 2019/03/20 06:11:03 by abguimba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/sh42.h"

void	proto_heredoc(char **env, t_last *list, int fd)
{
	char	*str;

	str = NULL;
	while (ft_strcmp(str, list->next->name) != 0)
	{
		g_tracking.quotes = 3;
		get_key();
		if (g_tracking.quotes == 10)
			exit(0);
		str = ft_strdup(g_tracking.cmd);
		if (ft_strcmp(str, list->next->name) != 0)
			ft_putendl_fd(str, fd);
		ft_putchar_fd('\n', 2);
	}
	exit(0);
}

char	*filename(void)
{
	char	*new;
	char	*nbr;
	int		i;

	new = ft_strdup("/tmp/heredoc");
	g_tracking.herenbr++;
	nbr = ft_itoa(g_tracking.herenbr);
	if (!nbr)
		return (NULL);
	new = ft_strjoinfree(new, nbr, 3);
	while (access(new, F_OK) != -1)
	{
		free(new);
		new = ft_strdup("/tmp/heredoc");
		g_tracking.herenbr++;
		nbr = ft_itoa(g_tracking.herenbr);
		if (!nbr)
			return (NULL);
		new = ft_strjoinfree(new, nbr, 3);
	}
	return (new);
}

int		exec_create_heredoc(t_last **list_cmd)
{
	char	*file;
	int		fd;
	pid_t	father;

	file = filename();
	if ((fd = open(file, O_CREAT | O_RDWR)) == -1)
	{
		ft_putendl_fd("Couldn't create fich in /temp", 2);
		return (-1);
	}
	g_tracking.redir++;
	father = fork();
	if (father == 0)
		proto_heredoc(NULL, *list_cmd, fd);
	else
		wait(&father);
	close(fd);
	fd = open(file, O_RDONLY);
	g_tracking.mysh->set_fd->STDIN = fd;
	if (g_tracking.unlink == 1)
	{
		unlink(file);
		g_tracking.herenbr--;
	}
	return (0);
}

int		exec_create_file(t_last **list_cmd)
{
	if (its_indir(*list_cmd) && !its_heredoc(*list_cmd))
	{
		if ((g_tracking.mysh->set_fd->STDIN = out_redir(*list_cmd)) == -1)
			return (-1);
		*list_cmd = (*list_cmd)->next;
	}
	else if (its_heredoc(*list_cmd))
	{
		if (exec_create_heredoc(list_cmd) == -1)
			return (-1);
		*list_cmd = (*list_cmd)->next;
	}
	else
	{
		g_tracking.redir++;
		create_fich(*list_cmd);
		*list_cmd = (*list_cmd)->next;
	}
	return (0);
}
