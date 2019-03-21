/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_two_arg.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsiche <bsiche@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/20 05:31:34 by bsiche            #+#    #+#             */
/*   Updated: 2019/03/17 03:47:40 by bsiche           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh42.h"

int		check_size(char *filename)
{
	t_lstcontainer	*liste;
	char			**taab;
	t_list			*buf;
	int				i;

	taab = malloc(sizeof(char *) * 4);
	taab[0] = "ls";
	taab[1] = filename;
	liste = type_ls(2, taab);
	buf = NULL;
	if (liste)
		buf = ft_lstgetfirst(liste->firstelement);
	if (!buf)
	{
		free(taab);
		return (1);
	}
	i = ((t_ls*)buf->content)->size;
	free(taab);
	free_all(liste, NULL);
	if (i > 0)
		return (0);
	else
		return (1);
}

char	*get_perm(char *filename)
{
	t_lstcontainer	*liste;
	char			**taab;
	t_ls			*new_ls;
	char			*test;
	t_list			*buf;

	taab = malloc(sizeof(char *) * 4);
	taab[0] = "ls";
	taab[1] = filename;
	buf = NULL;
	liste = type_ls(2, taab);
	if (liste)
		buf = ft_lstgetfirst(liste->firstelement);
	if (!buf)
	{
		free(taab);
		return (NULL);
	}
	new_ls = buf->content;
	test = ft_strdup(new_ls->strpermission);
	free(taab);
	free_all(liste, NULL);
	return (test);
}

int		b_to_g(char **argv, char *permission)
{
	if (!permission)
		return (1);
	if (ft_strcmp(argv[0], "-b") == 0)
		if (permission[0] == 'b')
			return (0);
	if (ft_strcmp(argv[0], "-c") == 0)
		if (permission[0] == 'c')
			return (0);
	if (ft_strcmp(argv[0], "-d") == 0)
		if (permission[0] == 'd')
			return (0);
	if (ft_strcmp(argv[0], "-e") == 0)
		if (permission)
			return (0);
	if (ft_strcmp(argv[0], "-f") == 0)
		if (permission[0] == '-')
			return (0);
	if (ft_strcmp(argv[0], "-g") == 0)
		if (permission[6] == 's' || permission[6] == 'S')
			return (0);
	return (1);
}

int		rest_of_perm(char **argv, char *permission)
{
	if (!permission)
		return (1);
	if (ft_strcmp(argv[0], "-L") == 0)
		if (permission[0] == 'l')
			return (0);
	if (ft_strcmp(argv[0], "-p") == 0)
		if (permission[0] == 'p')
			return (0);
	if (ft_strcmp(argv[0], "-r") == 0)
		if (permission[1] == 'r')
			return (0);
	if (ft_strcmp(argv[0], "-S") == 0)
		if (permission[0] == 's')
			return (0);
	if (ft_strcmp(argv[0], "-u") == 0)
		if (permission[3] == 's' || permission[3] == 'S')
			return (0);
	if (ft_strcmp(argv[0], "-w") == 0)
		if (permission[2] == 'w')
			return (0);
	if (ft_strcmp(argv[0], "-x") == 0)
		if (permission[3] == 'x' || permission[3] == 's')
			return (0);
	return (1);
}

int		two_arg(char **argv, int i)
{
	char	*permission;

	permission = NULL;
	if (argv[0][0] != '-')
		return (1);
	if (argv[0][1] == 'z')
	{
		if (ft_strlen(argv[1]) == 0)
			return (0);
		return (1);
	}
	permission = get_perm(argv[1]);
	if (!permission)
		i = 1;
	if (argv[0][1] >= 'b' && argv[0][1] <= 'g')
		i = b_to_g(argv, permission);
	if (argv[0][1] == 'L' || argv[0][1] == 'p' || argv[0][1] == 'r'
	|| argv[0][1] == 'S' || argv[0][1] == 'w' || argv[0][1] == 'u'
	|| argv[0][1] == 'x')
		i = rest_of_perm(argv, permission);
	if (argv[0][1] == 's')
		i = check_size(argv[1]);
	free(permission);
	return (i);
}
