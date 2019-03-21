/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scan.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjose <mjose@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/20 05:42:59 by mjose             #+#    #+#             */
/*   Updated: 2019/03/09 06:05:47 by mjose            ###   ########.fr       */
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

void	scan_argument(char *arg, t_scan *info_arg, int simple, char quote)
{
	char	*new_arg;
	t_scan	*first;
	char	*orig_arg;
	int		i;

	new_arg = ft_strnew(ft_strlen(arg));
	orig_arg = arg;
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
	arg = orig_arg;
	info_arg = first;
}

t_scan	*new_scan(void)
{
	t_scan	*scan;

	scan = (t_scan *)malloc(sizeof(t_scan));
	scan->sstring = NULL;
	scan->error = -1;
	scan->next = NULL;
	return (scan);
}
