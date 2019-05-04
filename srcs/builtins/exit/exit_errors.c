/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_errors.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjose <mjose@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/15 12:52:33 by mjose             #+#    #+#             */
/*   Updated: 2019/04/18 02:10:31 by mjose            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh42.h"

int			exit_errors(int error)
{
	if (error == 0)
		ft_putendl_fd(SHELL_NAME": exit: too many arguments", 2);
	if (error == 1)
	{
		ft_putstr_fd(SHELL_NAME": exit: ", 2);
		ft_putendl_fd("a numerical value is expected", 2);
	}
	return (-1);
}
