/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hash_builtin.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abguimba <abguimba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/15 12:52:33 by mjose             #+#    #+#             */
/*   Updated: 2019/05/02 08:15:12 by abguimba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh42.h"

char		**tab_format_hash(char *binary)
{
	char	**new;

	if (!(new = ft_malloc(sizeof(char*) * 2)))
		return (NULL);
	new[0] = ft_strdup(binary);
	new[1] = NULL;
	return (new);
}

int			hash_update_commands(int j)
{
	int		lastvalue;
	char	**commandhold;
	t_hash	*tmp;
	int		index;

	index = 0;
	tmp = NULL;
	lastvalue = 0;
	commandhold = NULL;
	while (g_tracking.g_tab_exec[j])
	{
		free_tab(commandhold);
		commandhold = tab_format_hash(g_tracking.g_tab_exec[j]);
		if (!(test_exist_fonct(commandhold, 1, NULL, NULL)))
		{
			errors_hash(g_tracking.g_tab_exec[j], 1);
			lastvalue = -1;
		}
		else
			hash_update_helper(tmp, index, j, commandhold);
		j++;
	}
	free_tab(commandhold);
	return (lastvalue);
}

int			empty_hash_table(void)
{
	int		i;
	t_hash	*tmp;
	t_hash	*hold;

	i = 0;
	while (i < 27)
	{
		tmp = g_tracking.hashtable[i];
		while (tmp)
		{
			hold = tmp;
			tmp = tmp->nextbinary;
			ft_strdel(&hold->path);
			ft_strdel(&hold->binary);
			hold->nextbinary = NULL;
			ft_free(hold);
		}
		g_tracking.hashtable[i] = NULL;
		i++;
	}
	return (0);
}

void		ft_hash_output(void)
{
	int		i;
	int		spaces;
	t_hash	*tmp;

	i = 0;
	spaces = 0;
	while (i < 27)
	{
		tmp = g_tracking.hashtable[i];
		if (tmp)
			ft_hash_output_helper(tmp, spaces);
		i++;
	}
}

int			ft_hash(void)
{
	int		count;
	int		i;
	int		j;

	j = 1;
	if (g_tracking.g_tab_exec[j])
		return (ft_hash_arg(j));
	count = 0;
	i = 0;
	while (i < 27)
	{
		if (g_tracking.hashtable[i])
			count++;
		i++;
	}
	if (count == 0)
		return (errors_hash("420", 0));
	ft_putendl("hits    command");
	ft_hash_output();
	return (0);
}
