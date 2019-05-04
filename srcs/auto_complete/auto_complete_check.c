/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   auto_complete_check.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsiche <bsiche@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/06 02:02:49 by bsiche            #+#    #+#             */
/*   Updated: 2019/05/04 01:53:32 by bsiche           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh42.h"

void	check_hidden(void)
{
	char	*check;

	if (g_tracking.aut->word)
	{
		check = g_tracking.aut->word;
		if (check[0] == '.')
			g_tracking.aut->hidden = 1;
	}
}

int		check_slash(char *check)
{
	int		i;
	int		flag;

	i = 0;
	flag = 0;
	if (!check)
		return (0);
	while (check[i])
	{
		if (check[i] == '/' && is_escape(check, i) != 1)
			flag = 1;
		i++;
	}
	return (flag);
}

int		check_type(void)
{
	char	*check;
	int		i;

	check = g_tracking.aut->word;
	i = ft_strlen(check) - 1;
	if (check[0] == '/' || check[0] == '~')
		return (1);
	if (check[1] != '\0')
	{
		if (check[0] == '.' && check[1] == '/')
			return (1);
		if (check[0] == '$' && check[i] == '/')
			return (1);
		if (check[0] == '$' && check[1] == '{')
			return (2);
		if (check[2] != '\0')
			if (check[0] == '.' && check[1] == '.' && check[2] == '/')
				return (1);
		if (check[ft_strlen(check) - 1] == '/')
			return (1);
		if (check_slash(check) == 1)
			return (1);
	}
	return (0);
}
