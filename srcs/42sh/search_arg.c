/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   search_arg.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjose <mjose@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/27 18:06:56 by mjose             #+#    #+#             */
/*   Updated: 2019/05/03 00:33:10 by alsomvil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh42.h"

char	*search_symboll(char *str)
{
	int		i;
	char	*ret;

	i = 0;
	ret = NULL;
	if (str[i] && (str[i] == '|' || str[i] == '&'))
	{
		i++;
		if (str[i] && str[i] == str[i - 1])
			i++;
		ret = ft_strndup(str, i);
		return (ret);
	}
	else if (str[i] == ';')
		return (ft_strndup(str, 1));
	return (NULL);
}

char	*search_fd_reddir(char *str)
{
	int		i;
	char	*ret;

	i = 0;
	ret = NULL;
	while (str[i] && str[i] >= '0' && str[i] <= '9')
	{
		i++;
		if (i == 1 && str[i] && (str[i] == '>' || str[i] == '<'))
		{
			i++;
			if (str[i] && str[i] == str[i - 1])
				i++;
			if (str[i] && str[i] == '&')
				i++;
			ret = ft_strndup(str, i);
			return (ret);
		}
	}
	return (NULL);
}

char	*search_reddir(char *str)
{
	int		i;
	char	*ret;

	i = 0;
	ret = NULL;
	if (str[i] && (str[i] == '>' || str[i] == '<'))
	{
		i++;
		if (str[i] && str[i] == str[i - 1])
			i++;
		if (str[i] && str[i] == '&')
			i++;
		ret = ft_strndup(str, i);
		return (ret);
	}
	return (NULL);
}

char	*search_quote(char *str, int i, int *nb)
{
	char	*temp;

	temp = NULL;
	if (str[i] && str[i] == '"')
	{
		temp = its_quote(i, str, nb, '"');
		if (temp)
			return (temp);
	}
	else if (str[i] && str[i] == '\'')
	{
		temp = its_quote(i, str, nb, '\'');
		if (temp)
			return (temp);
	}
	return (NULL);
}

char	*search_normally_arg(char *str, int *nb, int i)
{
	char	*temp;

	i = 0;
	temp = NULL;
	while (str[i])
	{
		if ((temp = search_quote(str, i, nb)))
			return (temp);
		else if (str[i] == '$' && str[i + 1] && str[i + 1] == '{')
		{
			while (str[i] && str[i] != '}')
				i++;
			if (!str[i] || str[i] == ' ')
				return (ft_strndup(str, i));
		}
		else if (str[i] == ' ' || !its_not_symbol(str[i]))
			return (ft_strndup(str, i));
		else
			i++;
	}
	temp = ft_strndup(str, i);
	if (ft_strlen(temp) > 0)
		return (temp);
	ft_strdel(&temp);
	return (NULL);
}
