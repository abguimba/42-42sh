/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   user.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjose <mjose@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/29 04:41:48 by mjose             #+#    #+#             */
/*   Updated: 2019/02/14 07:21:43 by mjose            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expansions.h"

int		check_have_homedir(struct passwd *user_inf, char *tmp_usr)
{
	if (user_inf->pw_dir)
	{
		ft_strdel(&tmp_usr);
		return (1);
	}
	return (0);
}

int		have_homedir(char *to_transf)
{
	int				i;
	int				to;
	char			*tmp_usr;
	struct passwd	*user_inf;

	i = 1;
	while (to_transf[i] && to_transf[i] != '/')
		i++;
	tmp_usr = ft_strnew(i);
	to = i;
	i = 1;
	while (to_transf[i] && to_transf[i] != '/' && i < to)
	{
		tmp_usr[i - 1] = to_transf[i];
		i++;
	}
	if ((user_inf = getpwnam(tmp_usr)))
		if (check_have_homedir(user_inf, tmp_usr))
			return (1);
	ft_strdel(&tmp_usr);
	return (0);
}
