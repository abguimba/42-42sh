/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_fich.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abguimba <abguimba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/20 13:24:49 by alsomvil          #+#    #+#             */
/*   Updated: 2019/03/20 06:11:03 by abguimba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/sh42.h"

void		next_set_fd(char c, int fd)
{
	if (c == '0')
		g_tracking.mysh->set_fd->STDIN = fd;
	else if (c == '1')
		g_tracking.mysh->set_fd->STDOUT = fd;
	else if (c == '2')
		g_tracking.mysh->set_fd->STDERR = fd;
	else if (c == '3')
		g_tracking.mysh->set_fd->three = fd;
	else if (c == '4')
		g_tracking.mysh->set_fd->four = fd;
	else if (c == '5')
		g_tracking.mysh->set_fd->five = fd;
	else if (c == '6')
		g_tracking.mysh->set_fd->six = fd;
	else if (c == '7')
		g_tracking.mysh->set_fd->seven = fd;
	else if (c == '8')
		g_tracking.mysh->set_fd->eight = fd;
	else if (c == '9')
		g_tracking.mysh->set_fd->nine = fd;
}

void		set_fd(char c, int fd)
{
	if ((fd == 0 && g_tracking.mysh->set_fd->STDIN == 0) || (fd == 1
				&& g_tracking.mysh->set_fd->STDOUT == 1) || (fd == 2
					&& g_tracking.mysh->set_fd->STDERR == 2))
	{
		if (c == '0')
			dup2(g_tracking.mysh->set_fd->STDIN, fd);
		if (c == '1')
			dup2(g_tracking.mysh->set_fd->STDOUT, fd);
		if (c == '2')
			dup2(g_tracking.mysh->set_fd->STDERR, fd);
	}
	else
		next_set_fd(c, fd);
}

void		set_reddir_to_fd(t_last *list, int i)
{
	FILE	*fd_open;
	int		fd;

	fd_open = NULL;
	fd = 0;
	while (list->name[i] && list->name[i] > 47 && list->name[i] < 58)
		i++;
	if (i > 2)
	{
		printf("ERREUR FD : [%s]\n", list->name);
		return ;
	}
	if (list->next && ft_strlen(&list->next->name[i]) > 1)
	{
		printf("ERREUR FD : [%s]\n", &list->name[i]);
		return ;
	}
	if (list->next && list->next->name[0] > 47 && list->next->name[0] < 58)
		fd_open = fdopen(list->next->name[0] - '0', "r+");
	else if (list->next && (ft_strlen(list->next->name) == 1) && !ft_strcmp(list->next->name, "-"))
		fd = open("/dev/null", O_WRONLY);
	else
	{
		printf("ERREUR NAME FD : [%s]\n", list->next->name);
		return ;
	}
	if (fd)
		set_fd(list->name[0], fd);
	if (fd_open)
		set_fd(list->name[0], fd_open->_file);
}

void		set_reddir_fd(t_last *list, int i)
{
	t_last	*temp;
	int		fd_fich;

	fd_fich = 0;
	temp = NULL;
	i = 0;
	temp = list;
	while (temp->name[i] > 47 && temp->name[i] < 58)
		i++;
	while (temp->type != FICH)
		temp = temp->next;
	fd_fich = open(temp->name, O_CREAT | O_TRUNC | O_RDWR, 0644);
	if (i < 2)
		set_fd(list->name[0], fd_fich);
}

void		create_fich(t_last *list)
{
	int		i;
	int		ret;
	t_last	*temp;

	i = 0;
	temp = list;
	if (its_reddir_to_fd(list))
		set_reddir_to_fd(list, i);
	else if (its_reddir(list))
	{
		while (list->type != FICH)
			list = list->next;
		if (ft_strlen(temp->name) == 1)
			g_tracking.mysh->set_fd->STDOUT = open(list->name, O_CREAT
				| O_TRUNC | O_RDWR, 0644);
		else
			g_tracking.mysh->set_fd->STDOUT = open(list->name, O_CREAT
				| O_APPEND | O_RDWR, 0644);
	}
	else if (its_fd_reddir(list))
		set_reddir_fd(list, i);
}
