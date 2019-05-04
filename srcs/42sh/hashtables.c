/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hashtables.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abguimba <abguimba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/15 12:52:33 by mjose             #+#    #+#             */
/*   Updated: 2019/05/04 00:20:06 by abguimba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh42.h"

char		*hashed_command_helper(char **newtab, char **tab_exec, t_hash *tmp)
{
	char	*new;

	(void)tab_exec;
	newtab[0] = ft_strdup(tmp->path);
	free_tab(newtab);
	new = ft_strdup(tmp->path);
	return (new);
}

char		*hashed_command(char **tab_exec, int i)
{
	char	**newtab;
	t_hash	*tmp;

	while (tab_exec[0][i] && (tab_exec[0][i] <= 65 || tab_exec[0][i] > 122))
		i++;
	i = ft_tolower(tab_exec[0][i]) - 'a';
	if (i < 0 || i > 25 || !(ft_strchr(g_tracking.g_tab_exec[0], '/'))
		|| (i == 0 && tab_exec[0][i] != 'a'))
		return (NULL);
	newtab = tab_dup(tab_exec);
	ft_strdel(&newtab[0]);
	tmp = g_tracking.hashtable[i];
	while (tmp)
	{
		if (!(ft_strcmp(tmp->binary, tab_exec[0])))
			return (hashed_command_helper(newtab, tab_exec, tmp));
		tmp = tmp->nextbinary;
	}
	free_tab(tab_exec);
	free_tab(newtab);
	return (NULL);
}

t_hash		*new_binary_hash(char *binary, char *path, int hits)
{
	t_hash	*new;

	if (!(new = ft_malloc(sizeof(t_hash))))
		return (NULL);
	new->binary = ft_strdup(binary);
	new->path = ft_strdup(path);
	new->totalhits = hits;
	new->nextbinary = NULL;
	return (new);
}

void		insert_to_hashtable(int key, char *binary, char *path)
{
	t_hash	*tmp;

	tmp = g_tracking.hashtable[key];
	if (tmp)
	{
		while (ft_strcmp(binary, tmp->binary) && tmp->nextbinary)
			tmp = tmp->nextbinary;
		if (!(ft_strcmp(binary, tmp->binary)))
		{
			if (ft_strcmp(tmp->path, path))
			{
				ft_strdel(&tmp->path);
				tmp->path = ft_strdup(path);
			}
			tmp->totalhits += 1;
		}
		else
			tmp->nextbinary = new_binary_hash(binary, path, 1);
	}
	else
		g_tracking.hashtable[key] = new_binary_hash(binary, path, 1);
}

void		hash_binary(void)
{
	int		hashedvalue;
	char	*binaryhold;
	int		i;

	binaryhold = NULL;
	if (ft_strchr(g_tracking.g_tab_exec[0], '/'))
		return ;
	binaryhold = ft_strdup(g_tracking.g_tab_exec[0]);
	i = 0;
	while (binaryhold[i] && (binaryhold[i] <= 65 || binaryhold[i] > 122))
		i++;
	if (!(test_exist_fonct(g_tracking.g_tab_exec, 1, NULL, NULL)))
		return (ft_strdel(&binaryhold));
	hashedvalue = ft_tolower(binaryhold[i]) - 'a';
	if (hashedvalue >= 0 && hashedvalue <= 25)
		insert_to_hashtable(hashedvalue, binaryhold, g_tracking.g_tab_exec[0]);
	ft_strdel(&binaryhold);
}
