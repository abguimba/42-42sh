/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_tools.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjose <mjose@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/07 16:11:41 by mjose             #+#    #+#             */
/*   Updated: 2019/04/18 02:10:31 by mjose            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "environ.h"
#include "builtins.h"
#include "sh42.h"

void	assign_to_env_save_value(char *varname, char *varvalue, char *arg)
{
	init_var(&varname, &varvalue, arg);
	if (!varvalue)
		varvalue = ft_strdup(get_set_env_string(varname));
	if (!varvalue)
		varvalue = ft_strdup(get_env_string(varname));
	remove_set_env_string(varname);
	replace_env_str(varname, varvalue);
	update_envp();
	end_var(&varname, &varvalue);
}

void	assign_to_env_replace_value(char *varname, char *varvalue, char *arg)
{
	init_var(&varname, &varvalue, arg);
	if (have_setname(varname))
	{
		if (!varvalue || !varvalue[0])
		{
			ft_strdel(&varvalue);
			varvalue = ft_strdup(get_set_env_string(varname));
		}
		remove_set_env_string(varname);
		replace_env_str(varname, varvalue);
		update_envp();
	}
	end_var(&varname, &varvalue);
}

void	assign_to_env_if_not_exist(char *varname, char *varvalue, char *arg)
{
	init_var(&varname, &varvalue, arg);
	ft_strdel(&varvalue);
	varvalue = ft_strdup(get_set_env_string(varname));
	remove_set_env_string(varname);
	replace_env_str(varname, varvalue);
	end_var(&varname, &varvalue);
	update_envp();
}
