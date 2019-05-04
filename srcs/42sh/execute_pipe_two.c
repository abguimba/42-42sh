/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_pipe_two.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsiche <bsiche@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/10 15:02:07 by mjose             #+#    #+#             */
/*   Updated: 2019/05/03 04:47:14 by bsiche           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh42.h"

void		execute_two(char **tab_exec, char **tab_exec_hold)
{
	char	**envhold;
	int		ctrl;
	char	*path;

	path = NULL;
	ctrl = check_expand_tab(tab_exec_hold);
	if (is_builtin() || ctrl)
		ft_exit3(builtin_exec(NULL), 2);
	if ((path = hashed_command(tab_exec, 0)) && !ctrl)
		execute_three(tab_exec, tab_exec_hold, path);
	else if ((test_exist_fonct(tab_exec_hold, 2, NULL, NULL)) && !ctrl)
	{
		apply_env();
		envhold = init_envp(g_tracking.mysh->env);
		execve(tab_exec_hold[0], tab_exec_hold, envhold);
		exec_errors(tab_exec, 1);
		free_tabs_and_exit(envhold, tab_exec_hold);
	}
	ctrl = exec_errors(NULL, 1);
	free_two_tabs(tab_exec_hold, g_tracking.g_tab_exec);
	g_tracking.g_tab_exec = NULL;
	ft_exit3(ctrl, 2);
}

int			make_reddir(char **tab_reddir, int i)
{
	if (!tab_reddir)
		return (0);
	while (tab_reddir[i])
	{
		if (its_indir(tab_reddir[i]) || its_heredoc(tab_reddir[i]))
		{
			if ((out_redir(tab_reddir, i) == -1))
				if (exit_reddir() == -1)
					return (-1);
		}
		else
		{
			if ((create_fich(tab_reddir, i) == -1))
				return (-1);
		}
		i = i + 2;
	}
	return (0);
}

void		close_fd_copy(void)
{
	close(10);
	close(11);
	close(12);
}

void		pipe_2_exec(char **tab_exec, t_jobs *job, int readpipe)
{
	pid_t	pid0;

	if (!is_builtin())
		hash_binary();
	pid0 = fork();
	if (pid0 == 0)
	{
		close_fd_copy();
		if (g_tracking.mysh->tab_reddir != NULL
			&& make_reddir(g_tracking.mysh->tab_reddir, 0) == -1)
			exit(-1);
		set_jobs(job, pid0);
		dup2(readpipe, 0);
		if (readpipe > 2)
			close(readpipe);
		execute_two(tab_exec, tab_dup(tab_exec));
	}
	else
	{
		if (readpipe > 2)
			close(readpipe);
		set_new_process(job, pid0);
		g_tracking.mysh->errchk = 0;
		free_tab(tab_exec);
	}
}

void		execute_pipe_two(char **tab_exec, t_jobs *job, int readpipe,
		char ***tab_reddir)
{
	free_tab(g_tracking.g_tab_exec);
	g_tracking.g_tab_exec = NULL;
	g_tracking.g_tab_exec = tab_dup(tab_exec);
	if (!is_builtin_alone(0, 0) && tab_exec[0])
	{
		pipe_2_exec(tab_exec, job, readpipe);
		free_tab(*tab_reddir);
		*tab_reddir = NULL;
	}
	else
	{
		free_tab(tab_exec);
		g_tracking.builtin = 1;
	}
}
