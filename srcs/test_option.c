/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_option.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsiche <bsiche@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/09 01:25:24 by bsiche            #+#    #+#             */
/*   Updated: 2019/05/03 08:44:29 by bsiche           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh42.h"

t_lstcontainer		*init_test(char *path)
{
	int				fd;
	t_lstcontainer	*test_lst;
	char			*test;
	struct stat		path_stat;

	test_lst = NULL;
	fd = -1;
	stat(path, &path_stat);
	if (stat(path, &path_stat) == 0)
		if ((S_ISREG(path_stat.st_mode) != 0))
			fd = open(path, O_RDWR, 0777);
	test = NULL;
	if (fd == -1)
	{
		ft_putstr_fd("Failed to load test file", 2);
		return (NULL);
	}
	test_lst = lstcontainer_new();
	while (get_next_line(fd, &test) != 0)
		lstcontainer_add(test_lst, test);
	close(fd);
	return (test_lst);
}

t_list				*clean_jobs_next_tmp(char *line, t_list *tmp)
{
	jobs_notifications();
	jobs_update_current();
	ft_free(line);
	line = NULL;
	tmp = tmp->next;
	return (tmp);
}

void				test_loop(char **argv, char *line)
{
	t_lstcontainer	*test_lst;
	t_list			*tmp;

	if (!argv[2])
		return (ft_putendl("Test usage : -t [test_file]"));
	tcsetattr(0, TCSANOW, &g_tracking.default_term);
	test_lst = init_test(argv[2]);
	if (!test_lst)
		return ;
	tmp = test_lst->firstelement;
	while (tmp)
	{
		line = ft_strdup(tmp->content);
		if (g_tracking.interactive == 1 && g_tracking.linemode == 0)
			ft_putchar_fd('\n', 0);
		while (check_eol(line) != 0)
			line = end_line(line);
		tcsetattr(0, TCSANOW, &g_tracking.default_term);
		main_loop(line);
		tmp = clean_jobs_next_tmp(line, tmp);
	}
	ft_lstdel(test_lst->firstelement, 1);
	free(test_lst);
}
