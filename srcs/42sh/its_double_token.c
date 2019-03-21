/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   its_double_token.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alsomvil <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/18 18:17:07 by alsomvil          #+#    #+#             */
/*   Updated: 2019/03/18 18:18:48 by alsomvil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/sh42.h"

int		its_not_symbol(char c)
{
	if (c == '|' || c == '>' || c == '<' || c == '&' || c == ';')
		return (0);
	else
		return (1);
}

int		its_heredoc(t_last *list)
{
	int		i;

	i = 0;
	while (list->name[i] && list->name[i] > 47 && list->name[i] < 58)
		i++;
	if (list->name[i] && list->name[i] == '<'
			&& list->name[i + 1] && list->name[i + 1] == '<')
		return (1);
	return (0);
}

int		its_pipe(t_last *list)
{
	int		i;

	i = 0;
	if (list && list->name[i]
			&& ft_strlen(list->name) == 1 && list->name[i] == '|')
		return (1);
	return (0);
}

char	*its_quote(int i, char *str, int *nb, char c)
{
	char	*temp;
	char	*forjoin;

	temp = NULL;
	forjoin = NULL;
	i++;
	while (str[i] && str[i] != c)
		i++;
	i++;
	if (str[i] && (str[i] == '"' || str[i] == '\''))
		return (its_quote(i, str, nb, str[i]));
	while (str[i] && str[i] != ' ' && str[i] != '|' && str[i] != '&'
			&& str[i] != '>' && str[i] != '<' && str[i] != ';')
		i++;
	temp = ft_strndup(str, i);
	return (temp);
}

int		its_separator(t_last *list)
{
	if (ft_strlen(list->name) == 2)
	{
		if (list->name[0] == '|' || list->name[0] == '&')
			return (1);
	}
	else if (list->name[0] == ';')
		return (1);
	return (0);
}
