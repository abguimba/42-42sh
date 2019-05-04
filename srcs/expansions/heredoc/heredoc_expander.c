/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_expander.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjose <mjose@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/30 05:55:45 by mjose             #+#    #+#             */
/*   Updated: 2019/05/02 03:41:28 by mjose            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expansions.h"
#include "sh42.h"

char	*quote_escaper(char *str, char *run_str)
{
	int		i;
	int		count_q;
	char	*tmp;

	i = 0;
	count_q = 0;
	tmp = str;
	while (run_str[i])
	{
		if (run_str[i] == '\'' || run_str[i] == '\"')
			count_q++;
		i++;
	}
	ft_strdel(&run_str);
	run_str = (ft_strnew(i + count_q));
	i = 0;
	count_q = 0;
	while (tmp[i])
	{
		if (tmp[i] == '\'' || tmp[i] == '\"')
			run_str[count_q++] = '\\';
		run_str[count_q++] = tmp[i++];
	}
	return (run_str);
}

int		heredoc_expander(char **str)
{
	char	*run_str;
	int		i;

	g_tracking.mysh->in_here = 1;
	run_str = ft_strdup(*str);
	if ((i = check_basic_quotes(*str)) > 0 && i == 3)
		run_str = quote_escaper(*str, run_str);
	else if (i && i < 3)
		return (1);
	run_str = convert_backslash(run_str);
	if (*str[0])
		expand_transformer(&run_str, 1);
	g_tracking.mysh->in_here = 0;
	run_str = convert_back(run_str);
	run_str = remove_back(run_str, 0);
	if (str[0])
		if (g_tracking.mysh->err_expend || !run_str)
			return (1);
	if (str[0])
	{
		ft_strdel(str);
		*str = run_str;
	}
	return (0);
}
