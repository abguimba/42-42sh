/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   home.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjose <mjose@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/02 01:20:02 by mjose             #+#    #+#             */
/*   Updated: 2019/02/17 06:34:30 by mjose            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expansions.h"
#include "sh42.h"

char	*get_user_home(char *user)
{
	struct passwd	*user_inf;

	user_inf = getpwnam(user);
	return (ft_strdup(user_inf->pw_dir));
}

char	*get_home_value(void)
{
	char	*home;
	char	*user;
	char	*usertmp;

	if ((home = ft_strdup(get_env_string("HOME"))) && ft_strequ(home, ""))
		return (home);
	else if ((home = get_parm_string("HOME")) && ft_strequ(home, ""))
		return (home);
	else
		return (get_user_home(getlogin()));
	return (NULL);
}
