/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   completion.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjose <mjose@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/01 09:13:59 by mjose             #+#    #+#             */
/*   Updated: 2019/05/04 09:32:33 by mjose            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh42.h"

int		valid_bracket(char *line, int quote, int double_quote, int *accol)
{
	int		i;

	i = 0;
	if (line[i] == '$' && line[i + 1] && line[i + 1] == '{'
			&& quote % 2 == 0 && double_quote % 2 == 0)
	{
		(*accol)--;
		if (*accol < 0)
			return (1);
	}
	return (0);
}

int		ft_valid_bracket(char *line)
{
	int	i;
	int	accol;
	int	quote;
	int	double_quote;

	i = 0;
	accol = 0;
	quote = 0;
	double_quote = 0;
	while (line[i])
		i++;
	while (i >= 0)
	{
		if ((line[i] == '"' && is_escape(line, i) != 1))
			double_quote++;
		else if ((line[i] == '\'' && is_escape(line, i) != 1))
			quote++;
		else if ((line[i] == '}' && is_escape(line, i) != 1)
		&& quote % 2 == 0 && double_quote % 2 == 0)
			accol++;
		else if (valid_bracket(&line[i], quote, double_quote, &accol) == 1)
			return (1);
		i--;
	}
	return (0);
}

char	*check_bracket(char *line, int i)
{
	char	*ret;
	char	*join;

	ret = NULL;
	join = NULL;
	while (line[i])
		i++;
	g_tracking.quotes = 3;
	get_key();
	if (g_tracking.bracket == 10)
		ft_exit2(EXIT_SUCCESS);
	join = g_tracking.cmd;
	if (!ret)
		ret = ft_strdup(join);
	ft_putchar('\n');
	g_tracking.quotes = 0;
	ft_strdel(&g_tracking.cmd);
	ctrl_c();
	return (ret);
}
