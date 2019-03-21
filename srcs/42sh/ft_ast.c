/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ast.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abguimba <abguimba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/31 02:25:05 by alsomvil          #+#    #+#             */
/*   Updated: 2019/03/20 06:11:03 by abguimba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
#include "../../includes/sh42.h"

#define ORDER g_tracking.mysh->order
#define EXEC g_tracking.mysh->exec

t_tree		*new_branch(void)
{
	t_tree	*tree;

	tree = ft_memalloc(sizeof(t_tree));
	tree->list_cmd = NULL;
	tree->cmd = NULL;
	tree->right = NULL;
	tree->left = NULL;
	tree->prev = NULL;
	return (tree);
}

t_last		*search_or_and(t_last *list)
{
	t_last	*temp;
	t_last	*begin;

	begin = list;
	temp = NULL;
	while (list->prev)
	{
		if ((ft_strlen(list->name) == 2 && (list->name[0] == '|'
						|| list->name[0] == '&')) || (ft_strlen(list->name) == 1
						&& (list->name[0] == '&' || list->name[0] == ';')))
		{
			temp = list;
			list = begin;
			return (temp);
		}
		list = list->prev;
	}
	return (NULL);
}

void		add_branch(t_tree *tree, t_last *separator)
{
	tree->type = SEP;
	tree->cmd = ft_strdup(separator->name);
	tree->left = new_branch();
	tree->left->prev = tree;
	tree->right = new_branch();
	tree->right->prev = tree;
}

void		create_ast(t_tree *tree, t_last *list_command)
{
	t_last	*separator;

	while (list_command->next)
		list_command = list_command->next;
	while (list_command->prev)
	{
		if ((separator = search_or_and(list_command)))
		{
			add_branch(tree, separator);
			separator->prev->next = NULL;
			create_ast(tree->left, separator->prev);
			separator->prev = NULL;
			if (separator->next)
			{
				separator->next->prev = NULL;
				create_ast(tree->right, separator->next);
			}
			separator->next = NULL;
			return ;
		}
		list_command = list_command->prev;
	}
	tree->type = CMD;
	tree->list_cmd = list_command;
	return ;
}

void		ft_ast(t_last *list_command)
{
	t_tree	*tree;
	t_jobs	*job;

	tree = new_branch();
	create_ast(tree, list_command);
	if (tree->type == SEP)
	{
		execute_ast(tree, job);
	}
	else
		exec_command(tree->list_cmd, 0, job);
	return ;
}
