/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abguimba <abguimba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/15 12:52:33 by mjose             #+#    #+#             */
/*   Updated: 2019/05/03 10:51:38 by abguimba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh42.h"

void	free_tabs_and_exit(char **envhold, char **tab_exec_hold)
{
	free_tab(envhold);
	free_tab(tab_exec_hold);
	ft_exit3(EXIT_FAILURE, 2);
}

int		spaces_line_check(char *line)
{
	int			i;

	i = 0;
	while (line[i] != '\0')
	{
		if (line[i] != ' ' && line[i] != '\n' && line[i] != '\t'
				&& line[i] != '\v' && line[i] != '\r')
			return (1);
		i++;
	}
	return (0);
}

char	**tab_dup(char **tob)
{
	int			i;
	char		**new;

	i = 0;
	new = NULL;
	while (tob[i])
		i++;
	if (!(new = ft_malloc(sizeof(char*) * (i + 1))))
		return (NULL);
	i = 0;
	while (tob[i])
	{
		new[i] = ft_strdup(tob[i]);
		i++;
	}
	new[i] = NULL;
	return (new);
}

char	*unquote(char *eof)
{
	int		i;
	int		a;
	char	*new;

	if (!eof)
		return (ft_strdup(eof));
	if (ft_strlen(eof) < 2)
		return (ft_strdup(eof));
	new = NULL;
	i = ft_strlen(eof) - 1;
	a = 0;
	if (eof[a] == '\'' && eof[i] == '\'')
		g_tracking.herexpnd = 1;
	if (eof[a] == '"' && eof[i] == '"')
		g_tracking.herexpnd = 1;
	if (g_tracking.herexpnd == 1)
	{
		new = ft_strsub(eof, 1, i - 1, 0);
		return (new);
	}
	return (ft_strdup(eof));
}

char	*assign_reddir(char *orig)
{
	char	*new;

	new = ft_strdup(orig);
	new = convert_back(new);
	new = remove_back(new, 0);
	return (new);
}
