/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unsetenv.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abguimba <abguimba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/15 12:52:33 by mjose             #+#    #+#             */
/*   Updated: 2019/04/21 04:26:14 by abguimba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh42.h"

char		**unsetenv_del_value(char **toob, int len, int save)
{
	char	**teeb;
	int		i;
	int		j;

	while (toob[len])
		len++;
	if (!(teeb = ft_malloc(sizeof(char*) * len)))
		return (NULL);
	i = 0;
	j = 0;
	while (toob[i] != NULL)
	{
		if (i != save)
		{
			teeb[j] = ft_strdup(toob[i]);
			j++;
			i++;
		}
		else
			i++;
	}
	teeb[j] = NULL;
	free_tab(toob);
	return (teeb);
}

int			ft_unsetenv_helper(char **taab, int j, int i)
{
	char	**toob;

	toob = g_tracking.mysh->tab_env;
	if (toob[i])
	{
		while (toob[i])
		{
			j = 0;
			while (toob[i][j] != '\0' && taab[1][j] != '\0'
			&& toob[i][j] != '=' && toob[i][j] == taab[1][j])
				j++;
			if (taab[1][j] == '\0' && toob[i][j] == '='
			&& taab[1][j - 1] == toob[i][j - 1])
			{
				g_tracking.mysh->tab_env = unsetenv_del_value(toob, 0, i);
				return (0);
			}
			i++;
		}
	}
	return (0);
}

int			ft_unsetenv(void)
{
	char	**taab;
	int		count;
	int		i;

	taab = g_tracking.g_tab_exec;
	count = 0;
	while (taab[count])
		count++;
	if (count != 2)
		return (unsetenv_errors(0));
	else
	{
		i = 0;
		while (taab[1] && taab[1][i] != '\0')
		{
			if (taab[1][i] == '=')
				return (unsetenv_errors(1));
			i++;
		}
		return (ft_unsetenv_helper(taab, 0, 0));
	}
}
