/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_pwd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsiche <bsiche@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/19 23:40:16 by bsiche            #+#    #+#             */
/*   Updated: 2019/01/19 23:40:36 by bsiche           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh42.h"

char	*ft_true_pwd(void)
{
	char	*buf;
	char	*str;

	buf = ft_strnew(1024);
	getcwd(buf, 1024);
	str = ft_strdup(buf);
	free(buf);
	return (str);
}
