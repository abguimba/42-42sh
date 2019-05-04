/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mode.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjose <mjose@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/28 13:40:46 by bsiche            #+#    #+#             */
/*   Updated: 2019/04/18 02:10:31 by mjose            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh42.h"
#include <time.h>

char	ft_type(mode_t c)
{
	if (S_ISCHR(c))
		return ('c');
	if (S_ISREG(c))
		return ('-');
	if (S_ISBLK(c))
		return ('b');
	if (S_ISLNK(c))
		return ('l');
	if (S_ISFIFO(c))
		return ('p');
	if (S_ISSOCK(c))
		return ('s');
	if (S_ISDIR(c))
		return ('d');
	else
		return (c);
}

char	*ft_sticky(mode_t mode, char *str)
{
	if (mode & S_ISUID)
	{
		if (str[3] == 'x')
			str[3] = 's';
		else
			str[3] = 'S';
	}
	if (mode & S_ISGID)
	{
		if (str[6] == 'x')
			str[6] = 's';
		else
			str[6] = 'S';
	}
	if (mode & S_ISVTX)
	{
		if (str[9] == 'x')
			str[9] = 't';
		else
			str[9] = 'T';
	}
	return (str);
}

char	*ft_usrmode(mode_t mode)
{
	char	*str;

	if (!mode)
		return (NULL);
	str = ft_strnew(11);
	str[0] = ft_type(mode);
	str[1] = mode & S_IRUSR ? 'r' : '-';
	str[2] = mode & S_IWUSR ? 'w' : '-';
	str[3] = mode & S_IXUSR ? 'x' : '-';
	str[4] = mode & S_IRGRP ? 'r' : '-';
	str[5] = mode & S_IWGRP ? 'w' : '-';
	str[6] = mode & S_IXGRP ? 'x' : '-';
	str[7] = mode & S_IROTH ? 'r' : '-';
	str[8] = mode & S_IWOTH ? 'w' : '-';
	str[9] = mode & S_IXOTH ? 'x' : '-';
	str[10] = ' ';
	str = ft_sticky(mode, str);
	return (str);
}
