/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsiche <bsiche@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/17 23:37:20 by bsiche            #+#    #+#             */
/*   Updated: 2019/05/04 00:40:00 by bsiche           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh42.h"

void	set_up(char **argv, char **env)
{
	char	*line;

	line = NULL;
	if (GARBAGE == 1)
		garbage_init();
	cursorinit();
	init_shell(env);
	get_term();
	interactive_check_set_shell_group();
	set_shell_signal_handlers();
	g_tracking.hist_first = 0;
	if (argv[1] && ft_strcmp(argv[1], "-t") == 0)
		test_loop(argv, line);
}

void	cmd_lstdel(t_last *cmd)
{
	t_last	*element;
	t_last	*next;

	if (cmd == NULL)
		return ;
	element = cmd;
	while (element->prev)
		element = element->prev;
	while ((void *)element != NULL)
	{
		next = element->next;
		if (element->name)
			ft_strdel(&element->name);
		ft_memdel((void *)&element);
		element = next;
	}
}

void	cmd_exists(t_last *cmd, t_last *first_cmd)
{
	ft_ast(cmd);
	if (first_cmd)
		first_cmd = NULL;
	cmd = NULL;
}

void	main_loop(char *line)
{
	t_last	*cmd;
	t_last	*first_cmd;
	int		ret;

	ret = 0;
	if ((ft_strlen(line) > 0) && spaces_line_check(line)
	&& (cmd = ft_parseur(0, line, NULL, NULL)))
	{
		first_cmd = cmd;
		if (write(0, "c", 0) != -1)
			if (ft_strcmp(line, "\n") != 0 && ft_strlen(line) > 0
			&& line[0] >= 32)
				lstcontainer_add(g_tracking.mysh->hist,
				ft_strdup_nocar((convert_back(line))));
		convert_list(cmd);
		if (!(ret = error_lexer(cmd)))
		{
			if (cmd)
				cmd_exists(cmd, first_cmd);
		}
		else if (ret == -1)
			cmd_lstdel(cmd);
	}
	reset_all();
}

int		main(int argc, char **argv, char **env)
{
	char	*line;

	line = NULL;
	if (argc > 3)
		argc_error();
	set_up(argv, env);
	while (get_key() > 0)
	{
		line = ft_strdup(g_tracking.cmd);
		ft_free(g_tracking.cmd);
		line = parse_bang(line);
		g_tracking.cmd = NULL;
		if (g_tracking.interactive == 1 && g_tracking.linemode == 0)
			ft_putchar_fd('\n', 0);
		while (check_eol(line) != 0)
			line = end_line(line);
		g_tracking.quotes = 0;
		main_loop(line);
		jobs_notifications();
		jobs_update_current();
		ft_free(line);
		line = NULL;
	}
	return (0);
}
