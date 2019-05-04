/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   alias_and_env_tools.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abguimba <abguimba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/07 02:06:25 by bsiche            #+#    #+#             */
/*   Updated: 2019/04/19 02:45:14 by abguimba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh42.h"

int				free_taab_and_return(char **taab, int returncode)
{
	free_tab(taab);
	return (returncode);
}

int				check_for_quotes_tmpenv(char *str, int i, int singq, int doubq)
{
	(str[i] == '\'') ? singq++ : doubq++;
	i++;
	while (str[i] != '\0')
	{
		if (str[i] == '\'')
			singq--;
		else if (str[i] == '\"')
			doubq--;
		if (singq < 1 && doubq < 1)
			return (i);
		i++;
	}
	return (i);
}

int				next_separator_quotes_check_h(int save, char *str, int i)
{
	save = i;
	while (str[i] && (str[i] == '&' || str[i] == ';' || str[i] == '|'))
		i++;
	while (str[i])
	{
		if (str[i] == '\'' || str[i] == '\"')
			i = check_for_quotes_tmpenv(str, i, 0, 0);
		i++;
		if ((str[i] == '&' && str[i + 1] && (str[i + 1] == '&'
		|| is_spaces(str, i + 1, 1))) || str[i] == ';' || str[i] == '|')
			return (i);
	}
	return (i);
}

int				next_separator_quotes_check(char *str, int i, int save)
{
	if (i == 0)
	{
		while (str[i])
		{
			if (str[i] == '\'' || str[i] == '\"')
				i = check_for_quotes_tmpenv(str, i, 0, 0);
			i++;
			if ((str[i] == '&' && str[i + 1] && (str[i + 1] == '&'
			|| is_spaces(str, i + 1, 1))) || str[i] == ';' || str[i] == '|')
				return (i);
		}
	}
	else
		return (next_separator_quotes_check_h(save, str, i));
	return (i);
}
