/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   environ.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjose <mjose@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/06 02:28:31 by mjose             #+#    #+#             */
/*   Updated: 2019/04/22 05:11:34 by mjose            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "environ.h"
#include "expansions.h"
#include "sh42.h"

int		have_envname(char *var)
{
	t_list		*env;
	t_keyval	*buf;

	if (g_tracking.mysh->env != NULL)
	{
		env = g_tracking.mysh->env->firstelement;
		while (env)
		{
			buf = env->content;
			if (ft_strcmp(var, buf->key) == 0)
				return (1);
			env = env->next;
		}
	}
	if (g_tracking.mysh->set_env == NULL)
		return (0);
	return (have_setname(var));
}

int		replace_frm_env_and_cmd_rmv(int env_or_set, char *varname,
			char *varvalue, char **str)
{
	if (env_or_set == 1)
	{
		replace_env_str(varname, varvalue);
		update_envp();
		ft_strdel(str);
		*str = ft_strdup("true");
		return (1);
	}
	else if (env_or_set == 2 || !env_or_set)
	{
		replace_env_set_str(varname, varvalue);
		ft_strdel(str);
		*str = ft_strdup("true");
		return (1);
	}
	return (0);
}

int		is_to_chg_env(char **str)
{
	char	*run_str;
	char	*varname;
	char	*varvalue;
	int		env_or_set;

	run_str = *str;
	varname = NULL;
	varvalue = NULL;
	if (is_new_value(run_str))
	{
		init_var(&varname, &varvalue, run_str);
		env_or_set = have_envname(varname);
		expand_transformer(&varvalue, 2);
		if (replace_frm_env_and_cmd_rmv(env_or_set, varname, varvalue, str))
		{
			end_var(&varname, &varvalue);
			return (1);
		}
		end_var(&varname, &varvalue);
	}
	return (0);
}
