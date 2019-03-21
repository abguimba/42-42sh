/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   termsize.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsiche <bsiche@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/17 23:44:50 by bsiche            #+#    #+#             */
/*   Updated: 2018/12/18 20:41:41 by bsiche           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sys/ioctl.h>
#include <unistd.h>
#include "sh42.h"

int		maxsize(t_list *liste)
{
	t_list	*buf;
	t_ls	*tmp;
	size_t	max;
	size_t	i;

	buf = ft_lstgetfirst(liste);
	max = 0;
	while (buf != NULL)
	{
		tmp = buf->content;
		i = ft_strlen(tmp->name);
		if (i > max)
			max = i;
		buf = buf->next;
	}
	return (max);
}

char	*ft_blank(size_t i, size_t max)
{
	char	*blank;

	max = max - i;
	max++;
	blank = ft_strnew(max + 1);
	i = 0;
	while (i < max)
	{
		blank[i] = ' ';
		i++;
	}
	blank[i] = '\0';
	return (blank);
}

int		ft_strpad(t_list *liste, int g)
{
	size_t	i;
	char	*blank;
	t_list	*buf;
	t_ls	*tmp;
	size_t	max;

	buf = ft_lstgetfirst(liste);
	max = maxsize(liste);
	while (buf != NULL)
	{
		tmp = buf->content;
		i = ft_strlen(tmp->name);
		if (g == 1)
			tmp->name = ft_strjoinfree(tmp->name, "\033[0m", 1);
		blank = ft_blank(i, max);
		tmp->name = ft_strjoinfree(tmp->name, blank, 3);
		buf = buf->next;
	}
	return (getsize(max));
}

int		getsize(int max)
{
	struct winsize	ts;
	int				col;

	ioctl(0, TIOCGWINSZ, &ts);
	col = (ts.ws_col) / (max + 2);
	if (col < 1)
		col = 1;
	return (col);
}
