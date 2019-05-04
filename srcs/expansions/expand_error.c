/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_error.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjose <mjose@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/03 06:17:07 by mjose             #+#    #+#             */
/*   Updated: 2019/05/02 08:42:06 by mjose            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expansions.h"
#include "sh42.h"

void	print_exp_error(char *to_error, char **str)
{
	if (g_tracking.mysh->in_ast && !g_tracking.mysh->err_expend_printed)
	{
		ft_putstr_fd(SHELL_NAME, 2);
		ft_putstr_fd(": ${", 2);
		if (to_error)
			ft_putstr_fd(to_error, 2);
		ft_strdel(&to_error);
		ft_putendl_fd("}: bad substitution", 2);
		g_tracking.mysh->err_expend = 0;
		g_tracking.mysh->err_expend_printed = 1;
	}
	else
	{
		ft_strdel(str);
		*str = ft_strjoinfree("${", to_error, 2);
		*str = ft_strjoinfree(*str, "}", 1);
		g_tracking.mysh->err_expend = 1;
	}
}

void	print_exp_str_error(char *strerror, char **str)
{
	if (g_tracking.mysh->in_ast && !g_tracking.mysh->err_expend_printed)
	{
		ft_putstr_fd(SHELL_NAME, 2);
		ft_putstr_fd(": ", 2);
		if (strerror)
			ft_putstr_fd(strerror, 2);
		ft_putendl_fd(": bad substitution", 2);
	}
	else
	{
		ft_strdel(str);
		*str = ft_strjoinfree("${", strerror, 0);
		*str = ft_strjoinfree(*str, "}", 1);
		g_tracking.mysh->err_expend = 1;
	}
}

void	print_exp_invalid(char *error)
{
	if (g_tracking.mysh->in_ast && !g_tracking.mysh->err_expend_printed)
	{
		ft_putstr_fd(SHELL_NAME": ", 2);
		ft_putstr_fd(error, 2);
		ft_putendl_fd(": bad substitution", 2);
		g_tracking.mysh->err_expend = 0;
		g_tracking.mysh->err_expend_printed = 1;
	}
	else
		g_tracking.mysh->err_expend = 1;
}

void	print_exp_token_error(void)
{
	if (g_tracking.mysh->in_ast && !g_tracking.mysh->err_expend_printed)
	{
		ft_putstr_fd(SHELL_NAME, 2);
		ft_putendl_fd(": syntax error: operand expected.", 2);
		g_tracking.mysh->err_expend = 0;
		g_tracking.mysh->err_expend_printed = 1;
	}
	else
		g_tracking.mysh->err_expend = 1;
}
