/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   getusr.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsiche <bsiche@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/29 22:52:09 by bsiche            #+#    #+#             */
/*   Updated: 2018/12/18 20:21:06 by bsiche           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh42.h"

char	*ft_getusr(uid_t pw)
{
	struct passwd	*pwd;
	char			*usrname;

	errno = 0;
	if ((pwd = getpwuid(pw)) == NULL)
		usrname = ft_itoa(pw);
	else
		usrname = ft_strdup(pwd->pw_name);
	return (usrname);
}

char	*ft_getgroup(gid_t gr)
{
	struct group	*usrgroup;
	char			*usr;

	if ((usrgroup = getgrgid(gr)) == NULL)
		usr = ft_itoa(gr);
	else
		usr = ft_strdup(usrgroup->gr_name);
	return (usr);
}
