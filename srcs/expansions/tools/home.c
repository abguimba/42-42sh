/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   home.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjose <mjose@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/02 01:20:02 by mjose             #+#    #+#             */
/*   Updated: 2019/04/22 03:54:28 by mjose            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expansions.h"
#include "sh42.h"

char	*get_user_home(char *user)
{
	struct passwd	*user_inf;
	char			*home_dir;

	user_inf = getpwnam(user);
	if (user_inf)
	{
		home_dir = ft_strdup(user_inf->pw_dir);
		return (home_dir);
	}
	return (NULL);
}

char	*get_home_value(void)
{
	char	*home;

	home = NULL;
	if ((home = get_env_string("HOME")))
		return (ft_strdup(home));
	else if ((home = get_parm_string("HOME")))
		return (ft_strdup(home));
	else
		return (get_user_home(getlogin()));
	return (NULL);
}
