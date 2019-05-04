/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   alias_bin.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abguimba <abguimba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/17 23:37:20 by bsiche            #+#    #+#             */
/*   Updated: 2019/04/30 22:32:27 by abguimba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh42.h"

char		*aliased_line(char **taab, int i, int loop, char *hold)
{
	char	*memory;

	while (loop == 0)
	{
		loop = 0;
		i = 0;
		while (taab[i])
		{
			hold = ft_strdup(taab[i]);
			taab[i] = recursive_alias(taab[i]);
			if (g_tracking.aliasloop->alias_len != 0)
				taab[i] = check_if_next_alias(taab[i]);
			if (ft_strcmp(taab[i], hold))
			{
				memory = taab_to_line(taab, hold);
				hold = NULL;
				taab = line_to_taab(memory, 0, 0);
				continue ;
			}
			i++;
			ft_strdel(&hold);
		}
		loop++;
	}
	return (taab_to_line(taab, hold));
}

void		alias_swapper_helper(int i, int j, char *line, char **taab)
{
	int		hold;
	int		l;

	while (i < (int)ft_strlen(line))
	{
		hold = i;
		i = next_separator(line, i);
		if (!(taab[j] = ft_malloc(sizeof(char) * i + 1)))
			return ;
		l = 0;
		while (hold < i)
		{
			taab[j][l] = line[hold];
			l++;
			hold++;
		}
		taab[j][l] = '\0';
		j++;
	}
	taab[j] = NULL;
}

char		*alias_swapper(char *line, int i, int count)
{
	char	**taab;

	taab = line_to_taab(line, i, count);
	line = aliased_line(taab, 0, 0, NULL);
	return (line);
}

int			print_alias_lst(void)
{
	t_keyval		*tmp;
	t_list			*buf;

	buf = NULL;
	if (g_tracking.mysh->alias_lst)
		buf = ft_lstgetfirst(g_tracking.mysh->alias_lst->firstelement);
	while (buf)
	{
		tmp = buf->content;
		if (tmp)
			print_keyval(tmp);
		buf = buf->next;
	}
	return (0);
}

char		*return_alias(char *name)
{
	t_keyval		*tmp;
	t_list			*buf;

	if (!g_tracking.mysh->alias_lst || !name)
		return (NULL);
	buf = ft_lstgetfirst(g_tracking.mysh->alias_lst->firstelement);
	while (buf)
	{
		tmp = buf->content;
		if (tmp)
		{
			if (ft_strcmp(tmp->key, name) == 0)
				return (tmp->value);
		}
		buf = buf->next;
	}
	return (NULL);
}
