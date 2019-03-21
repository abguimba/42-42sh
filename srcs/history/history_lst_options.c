/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history_lst_options.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdufer <hdufer@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/16 15:14:07 by hdufer            #+#    #+#             */
/*   Updated: 2019/03/21 17:15:38 by hdufer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh42.h"

char	*create_path_hist(void)
{
	char	*path;
	char	*user;

	path = ft_strdup("/Users/");
	user = getlogin();
	path = ft_strjoinfree(path, user, 1);// MJOSE LINUX
	path = ft_strjoinfree(path, "/.42hist", 1);
	return (path);
}

void	hist_file_to_lst(void)
{
	int		fd;
	char	*line;
	char	*path;
	int		t;

	line = NULL;
	path = create_path_hist();
	fd = open(path, O_CREAT | O_APPEND | O_RDWR, 00777);
	free(path);
	if (fd < 0)
		ft_putendl_fd("Error while opening/creating .42hist", 2);
	if (g_tracking.mysh->hist == NULL)
		g_tracking.mysh->hist = hist_lst_create(NULL);
	while ((t = get_next_line(fd, &line)) == 1 && line != NULL)
	{
		if (ft_strcmp(line, "\n") != 0)
			hist_lst_add_next(g_tracking.mysh->hist, line);
		if (line)
			free(line);
		line = NULL;
	}
	free(line);
	line = NULL;
	close(fd);
}

void		hist_print_test(t_hist *hist, int i)
{
	if (hist->line)
	{
		while (i-- > 0)
			ft_putchar(' ');
		ft_putnbr(hist->index);
		ft_putchar(' ');
		ft_putendl(hist->line);
	}
}

void		hist_print_space(t_hist *hist_count, t_hist *hist)
{
	int i[4];

	while (hist)
	{
		i[1]= 0;
		i[2]= 0;
		i[3] = hist->index;
		i[0]= hist_count->index;
		while ((i[0]/= 10))
			i[1]++;
		while ((i[3] /= 10))
			i[2]++;
		i[1]-= i[2];
		hist_print_test(hist, i[1]);
		if (hist->next)
			hist = hist->next;
		else
			break;
		if (hist_count->previous)
			hist_count = hist_count->previous;
		else
			break;
	}
}

void		hist_print(t_hist *hist)
{
	t_hist *hist_count;

	hist_count = hist;
	while (hist_count && hist_count->next)
		hist_count = hist_count->next;
	while (hist && hist->previous)
		hist = hist->previous;
	hist_print_space(hist_count, hist);
	
}