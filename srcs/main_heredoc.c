/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_heredoc.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abguimba <abguimba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/15 12:52:33 by alsomvil          #+#    #+#             */
/*   Updated: 2019/03/20 06:11:03 by abguimba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "sh42.h"

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
	return (new);
}

void	proto_heredoc(char **env)
{
	int		fd;
	char	*str;
	char	*file;
	char	**argv;

	str = ft_strnew(0);
	file = filename();
	argv = malloc(sizeof(char*) * 2);
	argv[0] = ft_strdup("cat");
	argv[1] = NULL;
	fd = open(file, O_CREAT | O_RDWR);
	while (ft_strcmp(str, "end") != 0)
	{
		g_tracking.quotes = 3;
		get_key();
		if (g_tracking.quotes == 10)
			exit (0);
		str = ft_strdup(g_tracking.cmd);
		if (ft_strcmp(str, "end") != 0)
			ft_putendl_fd(str, fd);
		ft_putchar('\n');
	}
		close (fd);
		fd = open(file, O_RDONLY);
		if (g_tracking.unlink == 1)
		{
			unlink(file);
			g_tracking.herenbr--;
		}
		dup2(fd, 0);
		execve("/bin/cat", argv, env);
		exit(0);
}

void	fork_to_cat(char **env)
{
	pid_t			father;
	
	father = fork();
	if (father > 0)
	{
		wait(&father);
		ft_putendl("test");
		exit(0);
	}
	if (father == 0)
		proto_heredoc(env);	
}

int		main(int argc, char **argv, char **env)
{
	char	*line;
	t_tab	st_tab;
	t_env	st_env;
	t_last	*cmd;

	line = NULL;
	if (argc > 2)
		argc_error();
	argc = 0;
	if (ft_strcmp(argv[1], "-u") == 0)
		g_tracking.unlink = 1;
	else
		g_tracking.unlink = 0;	
	//	set_env(&st_env, env);
	// ft_siginit();
	cursorinit();
	init_shell(env);
	get_term();
	interactive_check_set_shell_group();
	set_shell_signal_handlers();
	fork_to_cat(env);
	/*
	while (get_key() > 0)
	{
		line = ft_strdup(g_tracking.cmd);
		free(g_tracking.cmd);
		g_tracking.cmd = NULL;
		tcsetattr(0, TCSANOW, &g_tracking.default_term);
		ft_putchar('\n');
		if ((line = shebang_parse_switch(line)) != NULL)
		{
			if ((ft_strlen(line) > 0) && spaces_line_check(line) && (cmd = ft_parseur(line)))
			{
				hist_lst_add_next(g_tracking.mysh->hist, line);
				convert_list(cmd);
				ft_ast(cmd);
			}
		}
		jobs_notifications();
		jobs_update_current();
		free(line);
		line = NULL;
	}*/
	return (0);
}