/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history_lst.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdufer <hdufer@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/08 15:00:21 by hdufer            #+#    #+#             */
/*   Updated: 2019/03/21 17:44:22 by hdufer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh42.h"
#include <errno.h>

void		hist_setup_file(void)
{
	int		fd;
	char	**line;

	line = ft_memalloc(sizeof(line));
	fd = open("/goinfre/.shell_history", O_CREAT | O_APPEND | O_RDWR, 00777);
	if (fd < 0)
		return ft_putendl_fd("Error while opening/creating .shell_history", 2);
	if (get_next_line(fd, line) == 1)
	{
		g_tracking.mysh->hist = hist_lst_create(*line);
		while (get_next_line(fd, line) == 1 && *line != NULL)
			hist_lst_add_next(g_tracking.mysh->hist, *line);
	}
	close(fd);
	free(line);
}

void		hist_lst_add_next(t_hist *hist, char *line)
{
	t_hist	*new_node;

	if (!hist)
	{
		g_tracking.mysh->hist = hist_lst_create(NULL);
		hist = g_tracking.mysh->hist;
	}
	while (hist->next != NULL)
		hist = hist->next;
	if (line)
	{
		new_node = ft_memalloc(sizeof(*new_node));
		new_node->index = hist->index + 1;
		new_node->line = ft_strdup(line);
		new_node->next = NULL;
		new_node->previous = hist;
		hist->next = new_node;
		g_tracking.histmax = new_node->index;
		line = NULL;
	}
}

t_hist		*hist_lst_create(char *line)
{
	t_hist	*new_lst;

	if ((new_lst = malloc(sizeof(*new_lst))) == NULL)
		return (NULL);
	new_lst->index = 0;
	new_lst->line = line;
	new_lst->next = NULL;
	new_lst->previous = NULL;
	return (new_lst);
}

t_hist		*hist_free(void)
{
	t_hist *tmp;
	if (g_tracking.mysh->hist)
	{
		while (g_tracking.mysh->hist->next)
			g_tracking.mysh->hist = g_tracking.mysh->hist->next;
		while(g_tracking.mysh->hist)
		{
			tmp = g_tracking.mysh->hist;
			g_tracking.mysh->hist = g_tracking.mysh->hist->previous;
			free(tmp->line);
			tmp->line = NULL;
			free(tmp);
			tmp = NULL;
		}
	}
	g_tracking.mysh->hist = NULL;
	return (g_tracking.mysh->hist);
}
