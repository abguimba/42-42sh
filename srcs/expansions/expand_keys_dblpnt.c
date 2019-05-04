/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_keys_dblpnt.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjose <mjose@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/13 06:41:37 by mjose             #+#    #+#             */
/*   Updated: 2019/05/01 06:58:46 by mjose            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expansions.h"
#include "environ.h"
#include "sh42.h"

void	exp_key_plus(char **str, t_expand *expand)
{
	t_analyzer	to_analy;

	init_analyzer(&to_analy, str, expand);
	ft_strdel(str);
	if (!to_analy.vnme_len)
	{
		if (!g_tracking.mysh->in_here)
			print_exp_error_dpoints(to_analy.varname,
			to_analy.wildcard, '+', str);
		end_analyzer(to_analy);
		return ;
	}
	if (to_analy.varvalue && to_analy.varvalue[0])
	{
		if (to_analy.wildcard)
			*str = ft_strdup(to_analy.wildcard);
		else
			*str = ft_strdup("");
	}
	else
		*str = ft_strdup("");
	end_analyzer(to_analy);
}

void	exp_key_inter(char **str, t_expand *expand)
{
	t_analyzer	to_analy;

	init_analyzer(&to_analy, str, expand);
	if (to_analy.varvalue)
	{
		ft_strdel(str);
		*str = ft_strdup(to_analy.varvalue);
	}
	else if (to_analy.varname && to_analy.varname[0]
			&& !g_tracking.mysh->in_here)
		print_exp_error_inter(to_analy.varname, to_analy.wildcard, str);
	else if (!g_tracking.mysh->in_here)
		print_exp_error_dpoints(to_analy.varname, to_analy.wildcard, '?', str);
	end_analyzer(to_analy);
}

void	replace_to_null_error(char **str, t_analyzer to_analy)
{
	print_exp_error_dpoints(to_analy.varname, to_analy.wildcard, '=', str);
}

void	exp_key_equal(char **str, t_expand *expand)
{
	t_analyzer	to_analy;
	int			env_or_set;

	init_analyzer(&to_analy, str, expand);
	ft_strdel(str);
	env_or_set = have_envname(to_analy.varname);
	if (to_analy.varvalue && to_analy.varvalue[0])
		*str = ft_strdup(to_analy.varvalue);
	else if (env_or_set == 1)
	{
		replace_env_str(to_analy.varname, to_analy.wildcard);
		update_envp();
	}
	else if (env_or_set == 2 || (!env_or_set && to_analy.vnme_len))
		replace_env_set_str(to_analy.varname, to_analy.wildcard);
	else
		replace_to_null_error(str, to_analy);
	if (!*str)
	{
		if (to_analy.wildcard)
			*str = ft_strdup(to_analy.wildcard);
		else
			*str = ft_strdup(to_analy.varvalue);
	}
	end_analyzer(to_analy);
}

void	exp_key_less(char **str, t_expand *expand)
{
	t_analyzer	to_analy;

	init_analyzer(&to_analy, str, expand);
	ft_strdel(str);
	if (to_analy.varvalue && to_analy.varvalue[0])
		*str = ft_strdup(to_analy.varvalue);
	else if (!to_analy.varname[0] && !g_tracking.mysh->in_here)
		print_exp_error_dpoints(to_analy.varname, to_analy.wildcard, '-', str);
	else
		*str = ft_strdup(to_analy.wildcard);
	end_analyzer(to_analy);
}
