/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_quotes.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsiche <bsiche@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/01 05:54:46 by bsiche            #+#    #+#             */
/*   Updated: 2019/04/29 23:53:52 by bsiche           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh42.h"

char		*ft_puterror_missing_quotes(char *str)
{
	ft_putstr_fd("Missing quotes in cmd:", 2);
	ft_putendl_fd(str, 2);
	return (NULL);
}

int			ft_check_all(char *line)
{
	if (ft_valid_quote(line, '"', 0))
		return (1);
	else if (ft_valid_quote(line, '\'', 0))
		return (1);
	else if (ft_valid_bracket(line))
		return (1);
	return (0);
}

char		*quote_check(char *str)
{
	char	*line;
	int		i;

	i = 0;
	if (!str)
		return (NULL);
	while (str[i] == ' ')
		i++;
	line = ft_strdup(&str[i]);
	if (g_tracking.interactive == 0)
		if (check_basic_quotes(str) != 0)
		{
			ft_strdel(&line);
			return (ft_puterror_missing_quotes(str));
		}
	while (ft_check_all(line) == 1)
	{
		line = ft_modif_line(line);
		if (g_tracking.quotes == 10)
		{
			ft_strdel(&line);
			return (NULL);
		}
	}
	return (line);
}
