/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_command.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abguimba <abguimba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/18 16:40:13 by mjose             #+#    #+#             */
/*   Updated: 2019/05/03 00:42:58 by alsomvil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh42.h"

int		wait_job(int foreground, t_last *list_cmd, t_jobs *job,
		char ***tab_reddir)
{
	if (g_tracking.builtin == 0)
	{
		if (!g_tracking.interactive)
			wait_for_job(job);
		else if (!foreground)
			put_job_in_foreground(job, 0);
		else
			put_job_in_background(job, 0);
	}
	else
	{
		g_tracking.mysh->tab_reddir = *tab_reddir;
		save_fd();
		if (g_tracking.mysh->tab_reddir
				&& (make_reddir(g_tracking.mysh->tab_reddir, 0) == -1))
		{
			g_tracking.builtin = 0;
			return (clean_reddir(tab_reddir));
		}
		g_tracking.builtin = 0;
		g_tracking.lastreturn = builtin_exec(list_cmd);
		g_tracking.expandreturn = g_tracking.lastreturn;
	}
	jobs_notifications();
	return (clean_reddir(tab_reddir));
}

int		init_exec(t_last **list_cmd, t_jobs *job, int readpipe,
		char ***tab_reddir)
{
	if ((*list_cmd)->type == CMD)
	{
		g_tracking.temp_command = *list_cmd;
		*list_cmd = (*list_cmd)->next;
	}
	else if ((*list_cmd)->type == OP && its_pipe(*list_cmd)
			&& g_tracking.temp_command)
		return (execute_pipe(list_cmd, job, readpipe, tab_reddir));
	else if ((*list_cmd)->type == OP && its_pipe(*list_cmd)
			&& !g_tracking.temp_command)
	{
		if (*tab_reddir)
			execute_reddir(tab_reddir);
		*list_cmd = (*list_cmd)->next;
	}
	else if ((*list_cmd)->type == OP && (its_reddir(*list_cmd)
				|| its_fd_reddir(*list_cmd) || its_indir((*list_cmd)->name)))
	{
		save_reddir(list_cmd, tab_reddir);
		*list_cmd = (*list_cmd)->next;
	}
	else if (!g_tracking.temp_command || (*list_cmd)->type == FICH
			|| (*list_cmd)->type == OPT || (*list_cmd)->type == ARG)
		*list_cmd = (*list_cmd)->next;
	return (readpipe);
}

void	init_pipe_two(t_jobs *job, int readpipe, char ***tab_reddir)
{
	char	**tab_exec;

	tab_exec = NULL;
	tab_exec = create_tab_to_exec(g_tracking.temp_command);
	g_tracking.mysh->tab_reddir = NULL;
	g_tracking.mysh->tab_reddir = *tab_reddir;
	execute_pipe_two(tab_exec, job, readpipe, tab_reddir);
	g_tracking.mysh->tab_reddir = NULL;
	tab_exec = NULL;
	g_tracking.temp_command = NULL;
}

int		exec_command(t_last *list_cmd, int foreg, t_jobs *job, int readp)
{
	char	**tab_exec;
	char	**tab_reddir;

	tab_exec = NULL;
	tab_reddir = NULL;
	g_tracking.temp_command = NULL;
	g_tracking.mysh->errchk = 0;
	save_fd();
	if (!list_cmd)
		return (0);
	job = new_job(list_cmd, foreg);
	job->foreground = 1;
	while (list_cmd)
	{
		if ((readp = init_exec(&list_cmd, job, readp, &tab_reddir)) == -1)
			return (-1);
		if (g_tracking.temp_command && !list_cmd)
			init_pipe_two(job, readp, &tab_reddir);
	}
	if (tab_reddir && g_tracking.builtin != 1)
		execute_reddir(&tab_reddir);
	close_fd();
	restore_fd();
	return (wait_job(foreg, list_cmd, job, &tab_reddir));
}
