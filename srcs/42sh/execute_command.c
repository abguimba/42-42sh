/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_command.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abguimba <abguimba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/18 16:40:13 by alsomvil          #+#    #+#             */
/*   Updated: 2019/03/20 06:11:03 by abguimba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/sh42.h"

int		init_exec(t_last **list_cmd, t_jobs *job)
{
	if ((*list_cmd)->type == CMD)
	{
		g_tracking.temp_command = *list_cmd;
		*list_cmd = (*list_cmd)->next;
	}
	else if ((*list_cmd)->type == OP && its_pipe(*list_cmd)
			&& g_tracking.temp_command && g_tracking.redir == 0)
		exec_in_pipe(*list_cmd, job);
	else if ((*list_cmd)->type == OP && (its_reddir(*list_cmd)
				|| its_fd_reddir(*list_cmd) || its_indir(*list_cmd)))
	{
		if (exec_create_file(list_cmd) == -1)
			return (-1);
	}
	else if (!g_tracking.temp_command)
		*list_cmd = (*list_cmd)->next;
	else if ((*list_cmd)->type == FICH || (*list_cmd)->type == OPT
			|| (*list_cmd)->type == ARG)
		*list_cmd = (*list_cmd)->next;
	return (0);
}

void	wait_job(int foreground, t_last *list_cmd, t_jobs *job)
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
		g_tracking.builtin = 0;
		g_tracking.lastreturn = builtin_exec(list_cmd);
	}
}

void	close_descrf(void)
{
	if (descrf_two[0])
	{
		close(descrf_two[0]);
		close(descrf_two[1]);
	}
	if (descrf[0])
	{
		close(descrf[0]);
		close(descrf[1]);
	}
}

int		exec_command(t_last *list_cmd, int foreground, t_jobs *job)
{
	char	**tab_exec;

	tab_exec = NULL;
	g_tracking.temp_command = NULL;
	if (!list_cmd)
		return (0);
	job = new_job(list_cmd, foreground);
	set_fd_and_descr();
	while (list_cmd)
	{
		if (init_exec(&list_cmd, job) == -1)
			return (-1);
		if (g_tracking.temp_command && (!list_cmd
					|| ((its_pipe(list_cmd) && g_tracking.redir != 0))))
		{
			tab_exec = create_tab_to_exec(g_tracking.temp_command);
			execute_pipe_two(tab_exec, job);
			tab_exec = NULL;
			g_tracking.temp_command = NULL;
			g_tracking.redir = 0;
		}
	}
	wait_job(foreground, list_cmd, job);
	close_descrf();
	return (0);
}
