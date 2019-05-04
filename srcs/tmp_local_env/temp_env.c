/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   temp_env.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abguimba <abguimba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/29 12:23:43 by mjose             #+#    #+#             */
/*   Updated: 2019/04/29 05:13:20 by abguimba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh42.h"

int		is_for_tmpenv(char *arg)
{
	char	*run_arg;

	run_arg = arg;
	while (*run_arg)
	{
		if (run_arg[0] == '=')
			if (run_arg[-1])
				if (run_arg[1])
					return (1);
		run_arg++;
	}
	return (0);
}

void	assign_to_tmpenv(char *arg, char **var_name, char **var_value)
{
	char	*run_arg;
	char	*run_vname;
	char	*run_vvlue;

	run_arg = arg;
	run_vname = *var_name;
	run_vvlue = *var_value;
	while (run_arg && run_arg[0] != '=')
	{
		run_vname[0] = run_arg[0];
		run_vname++;
		run_arg++;
	}
	run_arg++;
	while (run_arg && run_arg[0])
	{
		run_vvlue[0] = run_arg[0];
		run_vvlue++;
		run_arg++;
	}
}

void	argenv_checker(char **arg)
{
	char	*var_name;
	char	*var_value;
	char	*run_arg;

	run_arg = *arg;
	if (run_arg[0] == '$')
		return ;
	if (run_arg && is_for_tmpenv(run_arg))
	{
		var_name = ft_strnew(ft_strlen(run_arg));
		var_value = ft_strnew(ft_strlen(run_arg));
		assign_to_tmpenv(run_arg, &var_name, &var_value);
		replace_env_str(var_name, var_value);
		ft_strdel(&var_name);
		ft_strdel(&var_value);
		ft_strdel(arg);
		*arg = ft_strdup(" ");
	}
}
