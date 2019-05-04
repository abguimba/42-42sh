/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   basic_mode.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsiche <bsiche@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/01 04:53:50 by bsiche            #+#    #+#             */
/*   Updated: 2019/05/04 05:21:39 by bsiche           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh42.h"

int		check_basic_quotes(char *line)
{
	int		flag;

	flag = 0;
	if (!line || ft_strlen(line) < 1)
		return (0);
	if (ft_valid_quote(line, '\'', 0) != 0)
		flag++;
	if (ft_valid_quote(line, '\"', 0) != 0)
		flag++;
	if (ft_valid_bracket(line) != 0)
		flag++;
	return (flag);
}

int		basic_mode(void)
{
	char	*str;

	str = NULL;
	tcsetattr(0, TCSANOW, &g_tracking.default_term);
	if (get_next_line(0, &str) <= 0)
		return (-1);
	if (check_basic_quotes(str) == 0)
		g_tracking.cmd = ft_strdup(str);
	else
	{
		ft_putstr_fd("Missing quotes in cmd:", 2);
		ft_putendl_fd(str, 2);
		g_tracking.cmd = NULL;
	}
	g_tracking.str = NULL;
	ft_strdel(&str);
	return (0);
}
