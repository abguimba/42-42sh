/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scan.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjose <mjose@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/20 05:42:59 by mjose             #+#    #+#             */
/*   Updated: 2019/04/18 02:10:31 by mjose            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expansions.h"
#include "sh42.h"

int		scan_it(char *arg, char **new_arg)
{
	if (arg[0] == '~')
		return (scan_tilde(arg, new_arg));
	else if (arg[0] == '$')
		return (scan_dollar(arg, new_arg));
	return (scan_other(arg, new_arg));
}

void	scan_argument(char *arg, t_scan *info_arg)
{
	char	*new_arg;
	t_scan	*first;
	int		i;

	new_arg = ft_strnew(ft_strlen(arg));
	first = info_arg;
	while (arg[0])
	{
		i = scan_it(arg, &new_arg);
		info_arg->sstring = ft_strdup(new_arg);
		ft_strdel(&new_arg);
		if (arg[i])
			arg = arg + i;
		else
			break ;
		new_arg = ft_strnew(ft_strlen(arg));
		info_arg->next = new_scan();
		if (arg[0])
			info_arg = info_arg->next;
	}
	info_arg->next = new_scan();
	info_arg = first;
	ft_strdel(&new_arg);
}

t_scan	*new_scan(void)
{
	t_scan	*scan;

	scan = (t_scan *)ft_malloc(sizeof(t_scan));
	scan->sstring = NULL;
	scan->error = -1;
	scan->next = NULL;
	return (scan);
}

void	scan_lstdel(t_scan *scan)
{
	t_scan	*element;
	t_scan	*next;

	if (scan == NULL)
		return ;
	element = scan;
	while (element)
	{
		if (element->sstring)
			ft_strdel(&element->sstring);
		next = element->next;
		ft_memdel((void *)&element);
		element = next;
	}
}
