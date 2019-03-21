/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hash_builtin.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abguimba <abguimba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/15 12:52:33 by alsomvil          #+#    #+#             */
/*   Updated: 2019/03/20 06:11:03 by abguimba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "sh42.h"

char		**tab_format_hash(char *binary)
{
	char	**new;

	if (!(new = malloc(sizeof(char*) * 2)))
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

	lastvalue = 0;
	while (g_tracking.g_tab_exec[j])
	{
		commandhold = tab_format_hash(g_tracking.g_tab_exec[j]);
		if (!(test_exist_fonction(commandhold, 1)))
		{
			errors_hash(g_tracking.g_tab_exec[j], 1);
			lastvalue = -1;
		}
		else
		{
			index = hash_maker(g_tracking.g_tab_exec[j][0]);
			tmp = g_tracking.hashtable[index];
			while (tmp)
			{
				if (!(ft_strcmp(g_tracking.g_tab_exec[j], tmp->binary)))
				{
					ft_strdel(&tmp->path);
					tmp->path = ft_strdup(commandhold[0]);
					tmp->totalhits = 0;
					break ;
				}
				if (!tmp->nextbinary)
					break ;
				tmp = tmp->nextbinary;
			}
			if (tmp)
			{
				if (!tmp->nextbinary && ft_strcmp(g_tracking.g_tab_exec[j], tmp->binary))
					tmp->nextbinary = new_binary_hash(g_tracking.g_tab_exec[j], commandhold[0], 0);
			}
			else
			{
				g_tracking.hashtable[index] = new_binary_hash(g_tracking.g_tab_exec[j], commandhold[0], 0);
			}
		}
		j++;
		if (commandhold[0])
			ft_strdel(&commandhold[0]);
	}
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
			free(hold);
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
	int		totalhitshold;
	t_hash	*tmp;
	
	i = 0;
	while (i < 27)
	{
		tmp = g_tracking.hashtable[i];
		if (tmp)
		{
			while (tmp)
			{
				spaces = 3;
				totalhitshold = tmp->totalhits;
				while (totalhitshold / 10)
				{
					totalhitshold = totalhitshold / 10;
					spaces -= 1;
				}
				while (spaces-- > 0)
					ft_putchar(' ');
				ft_putnbr(tmp->totalhits);
				ft_putstr("    ");
				ft_putendl(tmp->path);
				tmp = tmp->nextbinary;
			}
		}
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
	{
		while (g_tracking.g_tab_exec[j] && g_tracking.g_tab_exec[j][0] == '-')
		{
			if (strchr(g_tracking.g_tab_exec[j], 'r'))
			{
				empty_hash_table();
				if (!(g_tracking.g_tab_exec[j + 1]))
					return (0);
			}
			if (g_tracking.g_tab_exec[j] && g_tracking.g_tab_exec[j][1] != 'r')
				errors_hash(g_tracking.g_tab_exec[j], 2);
			j++;
		}
		if (g_tracking.g_tab_exec[j])
			return (hash_update_commands(j));
		return (0);
	}
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
