/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setenv.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abguimba <abguimba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/15 12:52:33 by mjose             #+#    #+#             */
/*   Updated: 2019/04/21 04:29:19 by abguimba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh42.h"

char		*new_setenv_maker(char **taab)
{
	int		i;
	int		j;
	char	*new;
	int		len;

	len = ft_strlen(taab[1]) + ft_strlen(taab[2]);
	if (!(new = ft_malloc(sizeof(char) * len + 2)))
		return (NULL);
	i = 0;
	j = 0;
	while (taab[1][i] != '\0')
	{
		new[i] = taab[1][i];
		i++;
	}
	new[i++] = '=';
	if (taab[2])
		while (taab[2][j] != '\0')
		{
			new[i] = taab[2][j];
			i++;
			j++;
		}
	new[i] = '\0';
	return (new);
}

char		**setenv_swap_values(int mode, char **toob, char **taab, int len)
{
	char	**teeb;
	int		i;

	if (mode == 0)
	{
		ft_strdel(&toob[len]);
		toob[len] = new_setenv_maker(taab);
		return (toob);
	}
	else
	{
		if (!(teeb = ft_malloc(sizeof(char*) * (len + 2))))
			return (NULL);
		i = 0;
		while (toob[i] != NULL)
		{
			teeb[i] = ft_strdup(toob[i]);
			i++;
		}
		teeb[i] = new_setenv_maker(taab);
		i++;
		teeb[i] = NULL;
		free_tab(toob);
		return (teeb);
	}
}

int			ft_setenv_helper(char **taab, int j, int i)
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
				toob = setenv_swap_values(0, toob, taab, i);
				return (0);
			}
			i++;
		}
		g_tracking.mysh->tab_env = setenv_swap_values(1, toob, taab, i);
	}
	return (0);
}

int			ft_setenv(void)
{
	char	**taab;
	int		count;
	int		i;

	taab = g_tracking.g_tab_exec;
	count = 0;
	while (taab[count])
		count++;
	if (count != 3)
		return (setenv_errors(0));
	else
	{
		i = 0;
		while (taab[1] && taab[1][i] != '\0')
		{
			if (taab[1][i] == '=')
				return (setenv_errors(1));
			i++;
		}
		return (ft_setenv_helper(taab, 0, 0));
	}
}
