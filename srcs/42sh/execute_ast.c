/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_ast.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abguimba <abguimba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/05 00:59:46 by alsomvil          #+#    #+#             */
/*   Updated: 2019/03/20 06:11:03 by abguimba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/sh42.h"
#include <stdlib.h>

void	set_fd_and_descr(void)
{
	descrf_two[0] = 0;
	descrf_two[1] = 0;
	descrf[0] = 0;
	descrf[1] = 0;
	g_tracking.redir = 0;
	g_tracking.mysh->set_fd = ft_memalloc(sizeof(t_set_fd));
	g_tracking.mysh->set_fd->STDIN = 0;
	g_tracking.mysh->set_fd->STDOUT = 1;
	g_tracking.mysh->set_fd->STDERR = 2;
}

void	exec_in_pipe(t_last *list_cmd, t_jobs *job)
{
	char	**tab_exec;

	tab_exec = create_tab_to_exec(g_tracking.temp_command);
	if (!descrf_two[0])
		pipe(descrf_two);
	if (!descrf[0])
		pipe(descrf);
	execute_pipe(tab_exec, job);
	tab_exec = NULL;
	g_tracking.temp_command = NULL;
	list_cmd = list_cmd->next;
}

void	exec_left_branch(t_tree *tree, t_jobs *job)
{
	if (ft_strlen(tree->cmd) == 1 && tree->cmd[0] == '&')
		g_tracking.foreground = 1;
	exec_command(tree->left->list_cmd, g_tracking.foreground, job);
	g_tracking.foreground = 0;
}

void	exec_right_branch(t_tree *tree, t_jobs *job)
{
	if (tree->prev && ft_strlen(tree->prev->cmd) == 1
			&& tree->prev->cmd[0] == '&')
		g_tracking.foreground = 1;
	exec_command(tree->right->list_cmd, g_tracking.foreground, job);
	g_tracking.foreground = 0;
}

void	execute_ast(t_tree *tree, t_jobs *job)
{
	g_tracking.foreground = 0;
	if (tree->type == SEP)
	{
		if (tree->left && tree->left->type != SEP)
			exec_left_branch(tree, job);
		else if (tree->left && tree->left->type == SEP)
			execute_ast(tree->left, job);
		if (ft_strlen(tree->cmd) > 1)
		{
			if (tree->cmd[0] == '&' && g_tracking.lastreturn == 1)
				return ;
			if (tree->cmd[0] == '|' && g_tracking.lastreturn == 0)
				return ;
		}
		if (tree->right && tree->right->type != SEP)
			exec_right_branch(tree, job);
		else if (tree->right)
			execute_ast(tree->right, job);
	}
	return ;
}
