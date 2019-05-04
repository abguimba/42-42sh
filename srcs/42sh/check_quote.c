/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_quote.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsiche <bsiche@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/16 16:47:21 by mjose             #+#    #+#             */
/*   Updated: 2019/04/29 02:32:15 by bsiche           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh42.h"

int		ft_valid_quote(char *line, char c, int flag)
{
	int		i;
	char	temp;

	i = 0;
	temp = (c == '"' ? '\'' : '"');
	if (!line)
		return (2);
	while (line[i])
	{
		if (line[i] == temp && flag == 0)
		{
			i++;
			while (line[i] && line[i] != temp)
				i++;
			if (!line[i])
				return (0);
		}
		else if ((line[i] == c && is_escape(line, i) != 1) && !flag)
			flag++;
		else if ((line[i] == c && is_escape(line, i) != 1) && flag)
			flag--;
		i++;
	}
	return (flag == 0 ? 0 : 1);
}

char	*del_tools(char **ret)
{
	ft_strdel(&g_tracking.cmd);
	ft_strdel(ret);
	ft_strdel(&g_tracking.str);
	return (NULL);
}

char	*check_quote(char c)
{
	char	*ret;
	int		test;

	ret = NULL;
	test = 1;
	while (test == 1)
	{
		ret = ft_strjoinchar(ret, '\n', 1);
		if (c == '"')
			g_tracking.quotes = 1;
		if (c == '\'')
			g_tracking.quotes = 2;
		get_key();
		if (g_tracking.quotes == 10)
			return (del_tools(&ret));
		test = ft_valid_quote(g_tracking.cmd, c, test);
		if (!ret)
			ret = ft_strdup(g_tracking.cmd);
		else
			ret = ft_strjoinfree(ret, g_tracking.cmd, 1);
		ft_putchar('\n');
		ft_strdel(&g_tracking.cmd);
	}
	g_tracking.quotes = 0;
	return (ret);
}
