/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmdparse_misc.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjose <mjose@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/19 22:28:10 by bsiche            #+#    #+#             */
/*   Updated: 2019/04/18 02:10:31 by mjose            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh42.h"

t_ls	*str_alloc(void)
{
	t_ls	*info;

	info = ft_malloc(sizeof(t_ls) + 1);
	info->name = NULL;
	info->path = NULL;
	info->symlink = NULL;
	info->strusrname = NULL;
	info->strgroup = NULL;
	info->strlink = NULL;
	info->strtime = NULL;
	info->strpermission = NULL;
	info->strsize = NULL;
	info->strmin = NULL;
	info->strmaj = NULL;
	info->timeswitch = 0;
	info->color = 0;
	info->issimple = 1;
	return (info);
}

void	ft_usage(char invalid)
{
	ft_putstr("ft_ls: illegal option -- -");
	ft_putchar(invalid);
	ft_putchar('\n');
	ft_putendl("usage: ft_ls [-1adlrtuSRG@] [file ...]");
	ft_exit2(EXIT_SUCCESS);
}

int		checkoption(char *option, char c)
{
	int		i;

	i = 0;
	while (option[i])
	{
		if (option[i] == c)
			return (1);
		i++;
	}
	return (0);
}

char	*clean1(char *option, int i, int j)
{
	char	*newstr;

	newstr = NULL;
	if (checkoption(option, '1') == 1 && checkoption(option, 'l') == 1)
	{
		newstr = ft_strnew(ft_strlen(option) - 1);
		while (option[i])
		{
			if (option[i] != '1')
			{
				newstr[j] = option[i];
				i++;
				j++;
			}
			else
				i++;
		}
		newstr[j] = '\0';
		ft_free(option);
		return (newstr);
	}
	return (option);
}
