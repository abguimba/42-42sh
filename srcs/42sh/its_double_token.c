/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   its_double_token.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abe <abe@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/18 18:17:07 by mjose             #+#    #+#             */
/*   Updated: 2019/04/30 13:56:19 by abe              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh42.h"

int		its_not_symbol(char c)
{
	if (c == '|' || c == '>' || c == '<' || c == '&' || c == ';')
		return (0);
	else
		return (1);
}

int		its_heredoc(char *str)
{
	int		i;

	i = 0;
	while (str[i] && str[i] > 47 && str[i] < 58)
		i++;
	if (str[i] && str[i] == '<'
			&& str[i + 1] && str[i + 1] == '<')
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
	if (str[i])
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

int		its_double_reddir(char *str)
{
	int		i;

	i = 0;
	while (str[i])
	{
		if (str[i] && str[i] == '>' && str[i + 1] && str[i + 1] == '>')
			return (1);
		i++;
	}
	return (0);
}
