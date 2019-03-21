/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history_lib_plus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsiche <bsiche@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/24 14:31:10 by hdufer            #+#    #+#             */
/*   Updated: 2019/03/20 03:24:26 by bsiche           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh42.h"

int			ft_isdigit_str(char* str)
{
	int i;

	i = 0;
	while(str[i])
	{
		if (ft_isdigit(str[i]) == 0)
			return (0);
		i++;
	}
	return (1);
}

char		*ft_strrdup(char *line, int n)
{
	char	*nline;
	int		i;

	i = 0;
	nline = ft_memalloc(sizeof(line) * n+1);
	if (!nline)
		return (NULL);
	while (line && n != i)
	{
		if(line[i])
			nline[i] = line[i];
		i++;
	}
	nline[i] = 0;
	return (nline);
}

int			ft_isspace(int c)
{
	if (c == ' ' || c == '\f' || c == '\r' || c == '\n')
		return (1);
	if (c == '\v' || c == '\t')
		return (1);
	return (0);
}

t_hist		*builtin_s_args(char **tabb, t_hist *hist)
{
	int i[3];
	char *str_ret;

	i[0] = 0;
	i[1] = 0;
	i[2] = 0;
	while(tabb[i[0]])
	{
		i[1] = 0;
		while(tabb[i[0]][i[1]])
			i[1]++;
		i[0]++;
	}
	str_ret = ft_memalloc(sizeof(char) * i[1]+i[0] + 1);
	i[0] = 0;
	i[1] = 0;
	while(tabb[i[0]])
	{
		i[1] = 0;
		while(tabb[i[0]][i[1]])
			str_ret[i[2]++] = tabb[i[0]][i[1]++];
		i[0]++;
		if (tabb[i[0]])
			str_ret[i[2]++] = ' ';
	}
	str_ret[i[2]] = 0;
	if (hist)
		hist_lst_add_next(hist, ft_strdup(str_ret));
	else
		hist = hist_lst_create(str_ret);
	return hist;
}