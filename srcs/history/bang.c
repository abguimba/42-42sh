/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bang.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsiche <bsiche@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/20 01:45:20 by bsiche            #+#    #+#             */
/*   Updated: 2019/05/03 09:13:39 by bsiche           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh42.h"

int		test_bang(char *line)
{
	int		flag;
	int		i;

	flag = 0;
	i = 0;
	while (line[i])
	{
		if (line[i] == '!' && (is_escape(line, i) == 0))
		{
			if (line[i + 1])
			{
				if (ft_isalnum(line[i + 1]) == 1)
					flag = 1;
				if (line[i + 1] == '!')
					flag = 1;
				if (line[i + 1] == '-')
					flag = 1;
				if (line[i + 1] == '!')
					flag = 1;
			}
		}
		i++;
	}
	return (flag);
}

char	*bang_apply(char *line)
{
	int		i;

	i = 0;
	while (line[i])
	{
		if (line[i] == '!' && is_escape(line, i) == 0)
		{
			if (line[i + 1])
			{
				if (ft_isspecial(line[i + 1]) == 1)
					return (replace_word(line, i));
				if (ft_isdigit(line[i + 1]) || line[i + 1] == '-')
					return (replace_word(line, i));
				if (line[i + 1] == '!')
					return (replace_double(line, i));
			}
		}
		i++;
	}
	return (line);
}

char	*parse_bang(char *line)
{
	int		i;

	i = 0;
	if (!line || ft_strlen(line) < 1)
		return (line);
	while (test_bang(line) != 0 && i < 50)
	{
		line = bang_apply(line);
		if (!line)
			break ;
		i++;
	}
	return (line);
}
