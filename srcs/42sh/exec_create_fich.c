/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_create_fich.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsiche <bsiche@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/18 16:42:28 by mjose             #+#    #+#             */
/*   Updated: 2019/05/03 08:44:27 by bsiche           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh42.h"

int		return_success(int i, char *file, char *key, int fd)
{
	ft_strdel(&key);
	close(fd);
	if (i == 1)
	{
		ft_strdel(&file);
		return (1);
	}
	if (i == 0)
	{
		if (g_tracking.cmd)
			ft_strdel(&g_tracking.cmd);
		if (g_tracking.str)
			ft_strdel(&g_tracking.str);
		if (g_tracking.herexpnd == 2)
		{
			ft_strdel(&file);
			ft_putendl_fd("42sh : Bad substitution", 2);
			return (1);
		}
		return (0);
	}
	return (0);
}

char	*get_str(void)
{
	char	*str;

	str = NULL;
	str = ft_strdup(g_tracking.cmd);
	str = convert_backslash(str);
	ft_strdel(&g_tracking.cmd);
	if (g_tracking.herexpnd != 1 && str)
	{
		heredoc_expander(&str);
		if (check_basic_quotes(str) != 0)
			g_tracking.herexpnd = 2;
	}
	if (!str)
		str = ft_strnew(1);
	return (str);
}

int		proto_heredoc(char *eof, int fd, char *file)
{
	char	*str;

	str = NULL;
	if (g_tracking.interactive == 0)
		return (0);
	eof = remove_back(eof, 0);
	while (ft_strcmp(str, eof) != 0 && g_tracking.quotes != 10)
	{
		ft_strdel(&str);
		g_tracking.quotes = 3;
		get_key();
		if (g_tracking.quotes == 11)
			return (return_success(1, file, eof, fd));
		str = get_str();
		if (ft_strcmp(str, eof) != 0)
			ft_putendl_fd(str, fd);
		ft_putchar_fd('\n', 2);
	}
	if (str)
		ft_free(str);
	return (return_success(0, NULL, eof, fd));
}

char	*filename(void)
{
	char	*new;
	char	*nbr;

	new = ft_strdup("/tmp/heredoc");
	g_tracking.herenbr++;
	nbr = ft_itoa(g_tracking.herenbr);
	if (!nbr)
		return (NULL);
	new = ft_strjoinfree(new, nbr, 3);
	while (access(new, F_OK) != -1)
	{
		ft_free(new);
		new = ft_strdup("/tmp/heredoc");
		g_tracking.herenbr++;
		nbr = ft_itoa(g_tracking.herenbr);
		if (!nbr)
			return (NULL);
		new = ft_strjoinfree(new, nbr, 3);
	}
	return (new);
}

char	*exec_create_heredoc(char *eof)
{
	char	*file;
	char	*key;
	int		fd;

	if (!eof || g_tracking.interactive != 1)
		return (NULL);
	file = filename();
	fd = 0;
	g_tracking.herexpnd = 0;
	key = unquote(eof);
	if ((fd = open(file, O_CREAT | O_RDWR, 0644)) == -1)
	{
		ft_putendl_fd("Couldn't create heredoc in /temp", 2);
		return (NULL);
	}
	if ((proto_heredoc(key, fd, file)) == 1)
	{
		ft_strdel(&g_tracking.str);
		return (NULL);
	}
	else
		return (file);
}
