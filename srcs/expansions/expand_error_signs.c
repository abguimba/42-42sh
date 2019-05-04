/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_error_signs.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjose <mjose@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/01 05:51:29 by mjose             #+#    #+#             */
/*   Updated: 2019/05/01 05:52:11 by mjose            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expansions.h"
#include "sh42.h"

void	print_exp_error_dpoints(char *varname, char *value, int sign,
			char **str)
{
	if (g_tracking.mysh->in_ast && !g_tracking.mysh->err_expend_printed)
	{
		ft_putstr_fd(SHELL_NAME, 2);
		ft_putstr_fd(": ${", 2);
		ft_putstr_fd(varname, 2);
		ft_putchar_fd(':', 2);
		ft_putchar_fd(sign, 2);
		ft_putstr_fd(value, 2);
		ft_putendl_fd("}: bad substitution", 2);
		g_tracking.mysh->err_expend = 0;
		g_tracking.mysh->err_expend_printed = 1;
	}
	else
	{
		ft_strdel(str);
		*str = ft_strjoinfree("${", varname, 0);
		*str = ft_strjoinchar(*str, ':', 1);
		*str = ft_strjoinchar(*str, sign, 1);
		*str = ft_strjoinfree(*str, value, 1);
		*str = ft_strjoinfree(*str, "}", 1);
		g_tracking.mysh->err_expend = 1;
	}
}

void	print_exp_error_eq(char *varname, char *value, char **str)
{
	if (g_tracking.mysh->in_ast && !g_tracking.mysh->err_expend_printed)
	{
		ft_putstr_fd(SHELL_NAME, 2);
		ft_putstr_fd(": ", 2);
		ft_putstr_fd(varname, 2);
		ft_putstr_fd(": ", 2);
		ft_putendl_fd(value, 2);
		g_tracking.mysh->err_expend = 0;
		g_tracking.mysh->err_expend_printed = 1;
	}
	else
	{
		ft_strdel(str);
		*str = ft_strjoinfree("${", varname, 0);
		*str = ft_strjoinfree(*str, ":=", 1);
		*str = ft_strjoinfree(*str, value, 1);
		*str = ft_strjoinfree(*str, "}", 1);
		g_tracking.mysh->err_expend = 1;
	}
}

void	print_exp_error_inter(char *varname, char *value, char **str)
{
	if (g_tracking.mysh->in_ast && !g_tracking.mysh->err_expend_printed)
	{
		ft_putstr_fd(SHELL_NAME, 2);
		ft_putstr_fd(": ", 2);
		ft_putstr_fd(varname, 2);
		ft_putstr_fd(": ", 2);
		ft_putendl_fd(value, 2);
		g_tracking.mysh->err_expend = 0;
		g_tracking.mysh->err_expend_printed = 1;
	}
	else
	{
		ft_strdel(str);
		*str = ft_strjoinfree("${", varname, 0);
		*str = ft_strjoinfree(*str, ":?", 1);
		*str = ft_strjoinfree(*str, value, 1);
		*str = ft_strjoinfree(*str, "}", 1);
		g_tracking.mysh->err_expend = 1;
	}
}
