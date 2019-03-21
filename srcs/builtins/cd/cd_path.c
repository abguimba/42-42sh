/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_path.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsiche <bsiche@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/28 19:07:24 by bsiche            #+#    #+#             */
/*   Updated: 2019/03/05 04:06:25 by bsiche           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh42.h"

char	*conc_and_free(char *path, char **taab)
{
	int i;

	i = 0;
	if (taab != NULL)
	{
		while (taab[i])
		{
			free(taab[i]);
			i++;
		}
	}
	free(taab);
	return (path);
}

char	*cd_line(char **taab, char *cdline, char *path)
{
	int i;

	i = 0;
	while (taab[i])
	{
		free(taab[i]);
		i++;
	}
	free(taab);
	free(path);
	return (cdline);
}

char	*ft_cdpath(char *path)
{
	char	**taab;
	char	*cdline;
	int		i;
	int		a;

	i = 0;
	taab = NULL;
	cdline = get_env_string("CDPATH");
	if (cdline)
		taab = ft_strsplit(cdline, ':');
	if (cdline)
		while (taab[i])
		{
			a = ft_strlen(taab[i]);
			if (taab[i][a] != '/')
				taab[i] = ft_strjoinfree(taab[i], "/", 1);
			cdline = ft_strjoinfree(taab[i], path, 0);
			if (ft_isdir(cdline) == 1)
				return (cd_line(taab, cdline, path));
			i++;
		}
	return (conc_and_free(path, taab));
}
