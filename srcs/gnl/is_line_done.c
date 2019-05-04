/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_line_done.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsiche <bsiche@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/06 22:47:40 by bsiche            #+#    #+#             */
/*   Updated: 2019/05/04 03:26:39 by bsiche           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh42.h"
#include "libft.h"

int		secondary_check(char *line)
{
	int		i;

	i = ft_strlen(line) - 1;
	if (i < 0)
		return (0);
	if (i == 0)
	{
		if (line[i] == '\\' && !line[i + 1])
			return (1);
	}
	if (line[i] == '\\' && (is_escape(line, i) != 1))
		return (1);
	if (line[i] == '|' && !line[i + 1])
		return (1);
	if (line[i] == '|' && is_escape(line, i) != 1)
		return (1);
	return (0);
}

int		check_eol(char *line)
{
	int		i;
	char	**taab;

	i = 0;
	if (g_tracking.quotes > 5 || g_tracking.interactive == 0 || !line)
		return (0);
	g_tracking.quotes = 0;
	taab = ft_split_whitespaces(line);
	if (taab)
	{
		while (taab[i])
			i++;
		i--;
		if (i > 0 && taab[i])
			if (ft_strcmp("&&", taab[i]) == 0 || ft_strcmp(taab[i], "||") == 0
			|| ft_strcmp(taab[i], "\\") == 0)
			{
				free_tab(taab);
				return (1);
			}
	}
	free_tab(taab);
	return (secondary_check(line));
}

char	*clean_and_return(char *line)
{
	ft_strdel(&g_tracking.cmd);
	g_tracking.cmd = NULL;
	ft_putchar('\n');
	return (line);
}

char	*end_line(char *line)
{
	int		flag;

	flag = 0;
	if (ft_valid_quote(line, '\'', 0) != 0)
		flag++;
	if (flag % 2 != 0)
		flag = 1;
	else
		flag = 0;
	g_tracking.quotes = 3;
	get_key();
	if (g_tracking.quotes > 3)
	{
		ft_strdel(&g_tracking.str);
		if (g_tracking.quotes == 11)
			ft_strdel(&line);
		return (line);
	}
	if (flag == 1)
		line = ft_strjoinfree(line, "\\\n", 1);
	if (ft_strlen(g_tracking.cmd) == 0
		|| ft_strcmp(g_tracking.cmd, "\\") == 0)
		line = remove_back(line, 0);
	line = ft_strjoinfree(line, g_tracking.cmd, 1);
	return (clean_and_return(line));
}
