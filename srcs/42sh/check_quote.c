/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_quote.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abguimba <abguimba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/16 16:47:21 by alsomvil          #+#    #+#             */
/*   Updated: 2019/03/20 06:11:03 by abguimba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/sh42.h"

int		ft_valid_quote(char *line, char c, int flag)
{
	int		i;
	char	temp;

	i = 0;
	temp = (c == '"' ? '\'' : '"');
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
		else if (line[i] == c && !flag)
			flag++;
		else if (line[i] == c && flag)
			flag--;
		i++;
	}
	return (flag == 0 ? 0 : 1);
}

char	*check_quote(char *line, int i, char c)
{
	char	*ret;
	int		test;

	ret = NULL;
	test = 1;
	while (line[i])
		i++;
	while (test == 1)
	{
		if (c == '"')
			g_tracking.quotes = 1;
		if (c == '\'')
			g_tracking.quotes = 2;
		get_key();
		if (g_tracking.quotes == 10)
			exit(0);
		test = ft_valid_quote(g_tracking.cmd, c, test);
		if (!ret)
			ret = ft_strdup(g_tracking.cmd);
		else
			ret = ft_strjoin(ret, g_tracking.cmd);
		ft_putchar('\n');
	}
	g_tracking.quotes = 0;
	return (ret);
}
