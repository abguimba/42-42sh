/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_pipe.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abe <abe@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/10 15:02:07 by mjose             #+#    #+#             */
/*   Updated: 2019/05/03 03:38:38 by alsomvil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh42.h"

void		close_fd(void)
{
	int		i;

	i = 0;
	while (i < 10)
		close(i++);
}

void		child_side(int rpipe, int *descrf, char **taab, t_jobs *job)
{
	close_fd_copy();
	dup2(rpipe, 0);
	if (rpipe > 2)
		close(rpipe);
	close(descrf[0]);
	dup2(descrf[1], 1);
	close(descrf[1]);
	if (g_tracking.mysh->tab_reddir)
	{
		if (make_reddir(g_tracking.mysh->tab_reddir, 0) == -1)
			exit(-1);
	}
	set_jobs(job, 0);
	execute_two(taab, tab_dup(taab));
}

int			exec_first_pipe(int rpipe, int *descrf, char **taab, t_jobs *job)
{
	pid_t	pid0;

	pid0 = fork();
	if (pid0 == 0)
		child_side(rpipe, descrf, taab, job);
	else
	{
		close(descrf[1]);
		if (rpipe > 2)
			close(rpipe);
		set_new_process(job, pid0);
		free_tab(taab);
		return (descrf[0]);
	}
	return (0);
}

int			return_end_pipe(char **tab_exec)
{
	if (tab_exec)
		free_tab(tab_exec);
	g_tracking.builtin = 1;
	return (0);
}

int			execute_pipe(t_last **list_cmd, t_jobs *job, int readpipe,
		char ***tab_reddir)
{
	char	**tab_exec;
	int		descrf[2];
	int		a;

	*list_cmd = (*list_cmd)->next;
	g_tracking.mysh->tab_reddir = NULL;
	g_tracking.mysh->tab_reddir = *tab_reddir;
	pipe(descrf);
	tab_exec = create_tab_to_exec(g_tracking.temp_command);
	free_tab(g_tracking.g_tab_exec);
	g_tracking.g_tab_exec = NULL;
	g_tracking.g_tab_exec = tab_dup(tab_exec);
	if (!is_builtin_alone(0, 0))
	{
		if (!is_builtin())
			hash_binary();
		a = exec_first_pipe(readpipe, descrf, tab_exec, job);
		free_tab(*tab_reddir);
		*tab_reddir = NULL;
		g_tracking.mysh->tab_reddir = NULL;
		if (a != 0)
			return (a);
	}
	return (return_end_pipe(tab_exec));
}
